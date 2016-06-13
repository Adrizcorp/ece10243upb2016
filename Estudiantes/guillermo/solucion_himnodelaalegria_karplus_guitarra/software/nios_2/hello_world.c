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

#include "./karplus/karplus.h"

int main()
{

	printf("Hello from Nios II!\n");
	init_karplus();
	set_karplus_frequency(44100);
	while(1)
	{
	//prueba
		/*play_tone(HIGH_E_0,1000);
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
		play_tone(LOW_E_9,1000);*/

	//himno de la alegria
	/*
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
		play_tone(HIGH_E_7,400);

	}
	return 0;
}
