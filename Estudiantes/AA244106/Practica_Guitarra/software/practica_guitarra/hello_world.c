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
	set_karplus_frequency(48000);
	while(1)
	{
		//fret 0
		play_tone(143,7000);
		play_tone(156,7000);
		play_tone(197,7000);
		play_tone(263,7000);
		play_tone(351,7000);
		play_tone(469,7000);

		//fret 1
		play_tone(135,6000);
		play_tone(147,6000);
		play_tone(186,6000);
		play_tone(248,6000);
		play_tone(331,6000);
		play_tone(442,6000);

		//fret 2
		play_tone(127,5000);
		play_tone(139,5000);
		play_tone(175,5000);
		play_tone(234,5000);
		play_tone(313,5000);
		play_tone(417,5000);

		//fret3
		play_tone(120,4000);
		play_tone(131,4000);
		play_tone(165,4000);
		play_tone(221,4000);
		play_tone(295,4000);
		play_tone(394,4000);

		//fret 4
		play_tone(113,3000);//High E
		play_tone(124,3000);//B
		play_tone(156,3000);//G
		play_tone(209,3000);//D
		play_tone(279,3000);//A
		play_tone(372,3000);//Low E

		//fret 5
		play_tone(107,2000);
		play_tone(117,2000);
		play_tone(147,2000);
		play_tone(197,2000);
		play_tone(263,2000);
		play_tone(351,2000);

		//fret 6
		play_tone(101,1000);
		play_tone(110,1000);
		play_tone(139,1000);
		play_tone(186,1000);
		play_tone(248,1000);
		play_tone(331,1000);

		//fret 7
		play_tone(95,500);
		play_tone(104,500);
		play_tone(131,500);
		play_tone(176,500);
		play_tone(234,500);
		play_tone(313,500);

		//fret 8
		play_tone(90,250);
		play_tone(98,250);
		play_tone(124,250);
		play_tone(166,250);
		play_tone(221,250);
		play_tone(295,250);

		//fret 9
		play_tone(85,125);
		play_tone(93,125);
		play_tone(117,125);
		play_tone(156,125);
		play_tone(209,125);
		play_tone(279,125);
	}
	return 0;
}
