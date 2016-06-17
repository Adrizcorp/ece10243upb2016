/*
 * karplus.c
 *
 *  Created on: 10/06/2016
 *      Author: Usuario
 */

#include "karplus.h"

void inject_noise(unsigned int karplus_base){
	int i;
	int noise;
	//NOISE ENABLE ON
	IOWR(karplus_base,1,1);
	for(i=0;i<500;i++)
	{
		noise=rand()*255;
		IOWR(karplus_base,0,noise & 0x7fff);
	}
	//NOISE ENABLE OFF
	IOWR(karplus_base,1,0);
}

void play_tone(unsigned int karplus_base,int nota, int time_ms){
	IOWR(karplus_base,1,1);
	IOWR(karplus_base,2,nota);
	inject_noise(karplus_base);
	usleep(time_ms*1000);
}

void set_karplus_frequency(unsigned int karplus_base,int frecuencia){
	int in_freq=(50000000/(2*frecuencia))-1;
	IOWR(karplus_base,4,in_freq);
}

void init_karplus(unsigned int karplus_base){
	IOWR(karplus_base,0,0);
	IOWR(karplus_base);
	IOWR(karplus_base,2,0);
	IOWR(karplus_base,3,0);

	set_karplus_frequency(karplus_base,44100);
}



