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
		play_tone(HIGH_E_0,100);
		play_tone(B_0,100);
		play_tone(G_0,100);
		play_tone(D_0,100);
		play_tone(A_0,100);
		play_tone(LOW_E_0,100);
		play_tone(HIGH_E_1,100);
		play_tone(B_1,100);
		play_tone(G_1,100);
		play_tone(D_1,100);
		play_tone(A_1,100);
		play_tone(LOW_E_1,100);
		play_tone(HIGH_E_2,100);
		play_tone(B_2,100);
		play_tone(G_2,100);
		play_tone(D_2,100);
		play_tone(A_2,100);
		play_tone(LOW_E_2,100);
		play_tone(HIGH_E_3,100);
		play_tone(B_3,100);
		play_tone(G_3,100);
		play_tone(D_3,100);
		play_tone(A_3,100);
		play_tone(LOW_E_3,100);
		play_tone(HIGH_E_4,100);
		play_tone(B_4,100);
		play_tone(G_4,100);
		play_tone(D_4,100);
		play_tone(A_4,100);
		play_tone(LOW_E_4,100);
		play_tone(HIGH_E_5,100);
		play_tone(B_5,100);
		play_tone(G_5,100);
		play_tone(D_5,100);
		play_tone(A_5,100);
		play_tone(LOW_E_5,100);
		play_tone(HIGH_E_6,100);
		play_tone(B_6,100);
		play_tone(G_6,100);
		play_tone(D_6,100);
		play_tone(A_6,100);
		play_tone(LOW_E_6,100);
		play_tone(HIGH_E_7,100);
		play_tone(B_7,100);
		play_tone(G_7,100);
		play_tone(D_7,100);
		play_tone(A_7,100);
		play_tone(LOW_E_7,100);
		play_tone(HIGH_E_8,100);
		play_tone(B_8,100);
		play_tone(G_8,100);
		play_tone(D_8,100);
		play_tone(A_8,100);
		play_tone(LOW_E_8,100);
		play_tone(HIGH_E_9,100);
		play_tone(B_9,100);
		play_tone(G_9,100);
		play_tone(D_9,100);
		play_tone(A_9,100);
		play_tone(LOW_E_9,100);
	}
	return 0;
}
