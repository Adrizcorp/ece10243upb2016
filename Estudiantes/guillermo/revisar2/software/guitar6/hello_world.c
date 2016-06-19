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

#define TIME 3
#define HIGH_E_4 113
#define B_4 124
#define G_4 156
#define D_4 209
#define A_4 279
#define LOW_E_4 372
#define HIGH_E_0 143
#define B_0 156
#define G_0 197
#define D_0 263
#define A_0 351
#define LOW_E_0 469
#define HIGH_E_1 135
#define B_1 147
#define G_1 186
#define D_1 248
#define A_1 331
#define LOW_E_1 442
#define HIGH_E_2 127
#define B_2 139
#define G_2 175
#define D_2 234
#define A_2 313
#define LOW_E_2 417
#define HIGH_E_3 120
#define B_3 131
#define G_3 165
#define D_3 221
#define A_3 295
#define LOW_E_3 394
#define HIGH_E_5 107
#define B_5 117
#define G_5 147
#define D_5 197
#define A_5 263
#define LOW_E_5 351
#define HIGH_E_6 101
#define B_6 110
#define G_6 139
#define D_6 186
#define A_6 248
#define LOW_E_6 331
#define HIGH_E_7 95
#define B_7 104
#define G_7 131
#define D_7 176
#define A_7 234
#define LOW_E_7 313
#define HIGH_E_8 90
#define B_8 98
#define G_8 124
#define D_8 166
#define A_8 221
#define LOW_E_8 295
#define HIGH_E_9 85
#define B_9 93
#define G_9 117
#define D_9 156
#define A_9 209
#define LOW_E_9 279
#define HIGH_E_10 80
#define HIGH_E_11 75
#define HIGH_E_12 71
#define B_10 88
#define B_12 78
#define silence 1

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


int main()
{

	printf("Hello from Nios II!\n");
	init_karplus();
	set_karplus_frequency(44100);
	while(1)
	{
	//prueba
		play_tone(HIGH_E_0,1000);
		play_tone(B_0,1000);
		play_tone(G_0,1000);
		play_tone(D_0,1000);
		play_tone(A_0,1000);
		play_tone(LOW_E_0,1000);
		play_tone(HIGH_E_1,1000);
		play_tone(B_1,1000);
		play_tone(G_1,1000);
		play_tone(D_1,1000);
		play_tone(A_1,1000);
		play_tone(LOW_E_1,1000);
		play_tone(HIGH_E_2,1000);
		play_tone(B_2,1000);
		play_tone(G_2,1000);
		play_tone(D_2,1000);
		play_tone(A_2,1000);
		play_tone(LOW_E_2,1000);
		play_tone(HIGH_E_3,1000);
		play_tone(B_3,1000);
		play_tone(G_3,1000);
		play_tone(D_3,1000);
		play_tone(A_3,1000);
		play_tone(LOW_E_3,1000);
		play_tone(HIGH_E_4,1000);
		play_tone(B_4,1000);
		play_tone(G_4,1000);
		play_tone(D_4,1000);
		play_tone(A_4,1000);
		play_tone(LOW_E_4,1000);
		play_tone(HIGH_E_5,1000);
		play_tone(B_5,1000);
		play_tone(G_5,1000);
		play_tone(D_5,1000);
		play_tone(A_5,1000);
		play_tone(LOW_E_5,1000);
		play_tone(HIGH_E_6,1000);
		play_tone(B_6,1000);
		play_tone(G_6,1000);
		play_tone(D_6,1000);
		play_tone(A_6,1000);
		play_tone(LOW_E_6,1000);
		play_tone(HIGH_E_7,1000);
		play_tone(B_7,1000);
		play_tone(G_7,1000);
		play_tone(D_7,1000);
		play_tone(A_7,1000);
		play_tone(LOW_E_7,1000);
		play_tone(HIGH_E_8,1000);
		play_tone(B_8,1000);
		play_tone(G_8,1000);
		play_tone(D_8,1000);
		play_tone(A_8,1000);
		play_tone(LOW_E_8,1000);
		play_tone(HIGH_E_9,1000);
		play_tone(B_9,1000);
		play_tone(G_9,1000);
		play_tone(D_9,1000);
		play_tone(A_9,1000);
		play_tone(LOW_E_9,1000);

	//himno de la alegria

	 /* play_tone(G_4,400);
	  play_tone(G_5,200);
	  play_tone(G_7,200);
	  play_tone(silence,1);
	  play_tone(G_7,200);
	  play_tone(G_5,200);
	  play_tone(G_4,200);
	  play_tone(G_2,200);
	  play_tone(G_0,200);
	  play_tone(silence,1);
	  play_tone(G_0,200);
	  play_tone(G_2,200);
	  play_tone(G_4,200);
	  play_tone(silence,1);
	  play_tone(G_4,300);
	  play_tone(G_2,100);
	  play_tone(silence,1);
	  play_tone(G_2,400);
	  play_tone(G_4,400);
	  play_tone(G_5,200);
	  play_tone(G_7,200);
	  play_tone(silence,1);
	  play_tone(G_7,200);
	  play_tone(G_5,200);
	  play_tone(G_4,200);
	  play_tone(G_2,200);
	  play_tone(G_0,200);
	  play_tone(silence,1);
	  play_tone(G_0,200);
	  play_tone(G_2,200);
	  play_tone(G_4,200);
	  play_tone(G_2,300);
	  play_tone(G_0,100);
	  play_tone(silence,1);
	  play_tone(G_0,400);
	  play_tone(silence,200);
	  play_tone(G_2,400);
	  play_tone(G_4,200);
	  play_tone(G_0,200);
	  play_tone(G_2,200);
	  play_tone(G_4,100);
	  play_tone(G_5,100);
	  play_tone(G_4,200);
	  play_tone(G_0,200);
	  play_tone(G_2,200);
	  play_tone(G_4,100);
	  play_tone(G_5,100);
	  play_tone(G_4,200);
	  play_tone(G_2,200);
	  play_tone(G_0,200);
	  play_tone(G_2,200);
	  play_tone(B_1,400);
	  play_tone(G_2,400);
	  play_tone(G_5,200);
	  play_tone(G_7,200);
	  play_tone(silence,1);
	  play_tone(G_7,200);
	  play_tone(G_5,200);
	  play_tone(G_4,200);
	  play_tone(G_2,200);
	  play_tone(G_0,200);
	  play_tone(silence,1);
	  play_tone(G_0,200);
	  play_tone(G_2,200);
	  play_tone(G_4,200);
	  play_tone(G_2,300);
	  play_tone(G_0,100);
	  play_tone(silence,1);
	  play_tone(G_0,400);
	  play_tone(silence,400);*/

	//O Christmas Tree Tannenbaum
	/*	play_tone(B_3,400);
		play_tone(HIGH_E_3,200);
		play_tone(HIGH_E_3,200);
		play_tone(HIGH_E_3,600);
		play_tone(HIGH_E_5,400);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_7,600);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_5,200);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_8,600);
		play_tone(HIGH_E_2,400);
		play_tone(HIGH_E_5,400);
		play_tone(HIGH_E_3,1000);
		play_tone(B_3,400);
		play_tone(HIGH_E_3,200);
		play_tone(HIGH_E_3,200);
		play_tone(HIGH_E_3,600);
		play_tone(HIGH_E_5,400);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_7,600);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_5,200);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_8,600);
		play_tone(HIGH_E_2,400);
		play_tone(HIGH_E_5,400);
		play_tone(HIGH_E_3,1000);
		//
		play_tone(HIGH_E_10,200);
		play_tone(HIGH_E_10,200);
		play_tone(B_12,200);
		play_tone(HIGH_E_12,400);
		play_tone(HIGH_E_10,200);
		play_tone(HIGH_E_10,200);
		play_tone(HIGH_E_8,200);
		play_tone(HIGH_E_8,400);
		play_tone(HIGH_E_8,200);
		play_tone(HIGH_E_8,200);
		play_tone(B_10,200);
		play_tone(HIGH_E_10,400);
		play_tone(HIGH_E_8,200);
		play_tone(HIGH_E_8,200);
		play_tone(HIGH_E_7,200);
		play_tone(HIGH_E_7,400);*/

	}
	return 0;
}
