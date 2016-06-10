/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //unix standard
#include <io.h> // I/O Access
#include <system.h>

unsigned char sr[469];
#define TIME 3

int main()
{//                 Mi  Si  Sol Do  La  Mi
	int p_notas[6]={143,156,197,263,351,469};
	int Fs = 16000;
	int ptrout = 2;
	int ptrin = 1;
	short sr[469];

	short out[16000*TIME];
	unsigned char sw_val=0;
	int i=0;
	char sw3=0;
	printf("Hello from Nios II!\n");
	while(1)
	{
		sw_val=IORD(SW_BASE,0);
		sw3=(sw_val>>3) &1;
		sw_val=sw_val & 7;
		sw_val=(sw_val%6);

		if(sw3){
			// Inicializacion Vector sr
			printf("init\n");
			for(i=0;i<p_notas[sw_val];i++)
			{

				sr[i]=rand()*255;
			}
			printf("generando muestras para %d\n",sw_val);
			for (i=0;i<Fs*TIME;i++)
			{

				out[i]=sr[ptrin];
				sr[ptrin] = (sr[ptrin]+sr[ptrout])/2;
				if (ptrin==p_notas[sw_val])
				{
					ptrin=0;
				}
				else
				{
					ptrin=ptrin+1;
				}
				if (ptrout==p_notas[sw_val])
				{
					ptrout=0;
				}
				else
					{
					ptrout=ptrout+1;
					}
				//printf("%d,",sr[ptrin]);

			}
			 printf("escuchando\n");
			 int delay;
			 for(i=0; i<Fs*TIME;i++){
				 IOWR(DIV_FREQ_BASE,0, out[i]);
				 usleep(10);
				// for(delay=0;delay<15;delay++);
			 }
		}

	//	IOWR(DIV_FREQ_BASE,0,DIV_FREQ_val);	//	usleep(100000);
	}
	return 0;
}
