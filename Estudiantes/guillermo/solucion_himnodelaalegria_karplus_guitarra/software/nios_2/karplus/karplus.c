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
	IOWR(NOISE_EN_BASE,0,1);
	for(i=0;i<500;i++)
				{

					noise=rand()*255;
					IOWR(NOISE_BASE,0,noise & 0x7fff);
					IOWR(NOISE_PULSE_BASE,0,0);
					usleep(1);
					IOWR(NOISE_PULSE_BASE,0,1);
					usleep(1);
				}
	IOWR(NOISE_PULSE_BASE,0,0);
	IOWR(NOISE_EN_BASE,0,0);
}

void play_tone(int nota, int time_ms){
	IOWR(NOISE_EN_BASE,0,1);
	IOWR(SEL_NOTA_BASE,0,nota);
	inject_noise();
	usleep(time_ms*1000);
}

void set_karplus_frequency(int frecuencia){
	int in_freq=(50000000/(2*frecuencia))-1;
	IOWR(DIV_FREQ_BASE,0,in_freq);
}

void init_karplus(){
	IOWR(NOISE_BASE,0,0);
	IOWR(NOISE_EN_BASE,0,0);
	IOWR(SEL_NOTA_BASE,0,0);
	IOWR(NOISE_PULSE_BASE,0,0);

	set_karplus_frequency(44100);
}



