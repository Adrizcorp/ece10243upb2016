/*
 * karplus.c
 *
 *  Created on: 10/06/2016
 *      Author: Usuario
 */

#include "karplus.h"

void inject_noise(){
	int i;
	int noise;
	IOWR(KARPLUS_STRONG_0_BASE,1,1);
	for(i=0;i<500;i++)
	{
		noise=rand()*255;
		IOWR(KARPLUS_STRONG_0_BASE,0,noise & 0x7fff);
		IOWR(KARPLUS_STRONG_0_BASE,3,0);
		usleep(1);
		IOWR(KARPLUS_STRONG_0_BASE,3,1);
		usleep(1);
	}
	IOWR(KARPLUS_STRONG_0_BASE,3,0);
	IOWR(KARPLUS_STRONG_0_BASE,1,0);
}

void play_tone(int nota, int time_ms){
	IOWR(KARPLUS_STRONG_0_BASE,1,1);
	IOWR(KARPLUS_STRONG_0_BASE,2,nota);
	inject_noise();
	usleep(time_ms*1000);
}

void set_karplus_frequency(int frecuencia){
	int in_freq=(50000000/(2*frecuencia))-1;
	IOWR(KARPLUS_STRONG_0_BASE,4,in_freq);
}

void init_karplus(){
	IOWR(KARPLUS_STRONG_0_BASE,0,0);
	IOWR(KARPLUS_STRONG_0_BASE,1,0);
	IOWR(KARPLUS_STRONG_0_BASE,2,0);
	IOWR(KARPLUS_STRONG_0_BASE,3,0);

	set_karplus_frequency(44100);
}



