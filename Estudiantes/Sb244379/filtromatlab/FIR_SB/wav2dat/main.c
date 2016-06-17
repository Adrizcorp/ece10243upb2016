//=======================================================================================
//=======================================================================================
// PROGRAMA 		: Convertidor de formato WAV to DAT
// FUNCIÓN 			: Práctica Proyecto de Grado
// REALIZADO POR	: Juan D. Prieto A.
// ORGANIZACIÓN		: Universidad pontificia Bolivariana
// FECHA 			: Marzo 2015
//=======================================================================================
//=======================================================================================

//=======================================================================================
// LIBRERIAS
//=======================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//=======================================================================================
// PARÁMETROS
//=======================================================================================


//=======================================================================================
// VARIABLES GLOBALES
//=======================================================================================

char riff[4],wave[4],fmt[4],stuf,data[4],sbyte[2];
short ccode,channels,blockalign,bps;
short aword;											// Audio Word
int sread,swrite,fsize,nbytes,rate,avgrate,csize,nbread;

//=======================================================================================
// EJECUCIÓN FILTRO FIR
//=======================================================================================
int main(int argc, char *argv[])
{
	FILE * inp;
	FILE * outp;

	int i;

	printf("WAV2DAT.c running \n");
	if(argc<2)
	{
		printf("Please choose a readable .wav file.\n");
		exit(1);
	}

	inp = fopen(argv[1], "rb");

	if(inp == NULL)
	{
		printf("%s was not found.\n", argv[1]);
		exit(1);
	}

	if(argc<3)
	{
		printf("No output file given. Saving as default.dat\n");
		outp = fopen("default.dat","wb");
		if(outp == NULL)
		{
			printf("Can't write default.dat, contact for help.\n");
			exit(1);
		}
	}
	else /* open users output file */
	{
		outp = fopen(argv[2], "wb");
		if(outp == NULL)
		{
			printf("Can't open %s for writing. \n", argv[2]);
			exit(1);
		}
	}

	printf("Reading %s ...\n\n", argv[1]);
	printf("WAV Header: \n");

	sread = fread(&riff[0], 1, 4, inp);
	printf("first 4 bytes should be RIFF: <%c%c%c%c>\n",riff[0],riff[1],riff[2],riff[3]);

	sread = fread(&fsize, 1, 4, inp);
	printf("file has: %d +8 bytes \n", fsize);

	sread = fread(&wave[0], 1, 4, inp);
	printf("should be WAVE: <%c%c%c%c>\n",wave[0],wave[1],wave[2],wave[3]);

	sread = fread(&fmt[0], 1, 4, inp);
	printf("should be fmt: <%c%c%c%c>\n",fmt[0],fmt[1],fmt[2],fmt[3]);

	sread = fread(&nbytes, 1, 4, inp);
	printf("block has: %d more bytes \n", nbytes);

	sread = fread(&ccode, 1, 2, inp);
	printf("compression code = %d \n", ccode);
	nbytes = nbytes-2;

	sread = fread(&channels, 1, 2, inp);
	printf("channels = %d \n", channels);
	nbytes = nbytes-2;

	sread = fread(&rate, 1, 4, inp);
	printf("rate = %d  \n", rate);
	nbytes = nbytes-4;

	sread = fread(&avgrate, 1, 4, inp);
	printf("avg rate = %d \n", avgrate);
	nbytes = nbytes-4;

	sread = fread(&blockalign, 1, 2, inp);
	printf("blockalign = %d  \n", blockalign);
	nbytes = nbytes-2;

	sread = fread(&bps, 1, 2, inp);
	printf("bits per sample = %d \n", bps);
	nbytes = nbytes-2;

	printf("bytes left in fmt = %d \n", nbytes);

	for(i=0; i<nbytes; i++)
	{
		sread = fread(&stuf, 1, 1, inp);
		swrite = fwrite(&stuf, 1, 1, outp);
	}

	sread = fread(&data[0], 1, 4, inp);
	printf("should be data: <%c%c%c%c>\n",data[0],data[1],data[2],data[3]);

	sread = fread(&csize, 1, 4, inp);
	printf("chunk has: %d more bytes \n", csize);

	nbread = 44+nbytes;
	printf("%d bytes read so far \n", nbread);

	int bad = 0;
	for(i=0; i<(csize/2); i++)
	{
		sread = fread(&sbyte[0], 1, 2, inp);
		aword=((sbyte[1]<<8) | (sbyte[0] & 0xff))& 0xffff;
		if(sread !=2 && bad==0)
		{
			bad=1;
			printf("no read on bytes: %d-%d\n", i,i+1);
		}
		fprintf(outp,"%d\n",aword);
	}

	nbread = nbread+csize;
	printf("%d bytes read so far \n", nbread);

	fclose(inp);
	fflush(outp);
	fclose(outp);
	printf("WAV2DAT.c done. New %s file written.\n", argv[2]);

	return(0);
}
