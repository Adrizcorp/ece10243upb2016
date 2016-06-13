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
#include "./karpus/karplus.h"

int main()
{

	printf("Hello from Nios II!\n");
	init_karplus();
	set_karplus_frequency(48000);
	while(1)
	{
		play_tone(143,3000);
		play_tone(156,3000);
		play_tone(197,3000);
		play_tone(263,3000);
		play_tone(351,3000);
		play_tone(469,3000);

		play_tone(135,3000);
		play_tone(147,3000);
		play_tone(186,3000);
		play_tone(248,3000);
		play_tone(331,3000);
		play_tone(442,3000);

		play_tone(127,3000);
		play_tone(139,3000);
		play_tone(175,3000);
		play_tone(234,3000);
		play_tone(313,3000);
		play_tone(417,3000);

		play_tone(120,3000);
		play_tone(131,3000);
		play_tone(165,3000);
		play_tone(221,3000);
		play_tone(295,3000);
		play_tone(394,3000);

		play_tone(113,3000);
		play_tone(124,3000);
		play_tone(156,3000);
		play_tone(209,3000);
		play_tone(279,3000);
		play_tone(372,3000);

		play_tone(107,3000);
		play_tone(117,3000);
		play_tone(147,3000);
		play_tone(197,3000);
		play_tone(263,3000);
		play_tone(351,3000);

		play_tone(101,3000);
		play_tone(110,3000);
		play_tone(139,3000);
		play_tone(186,3000);
		play_tone(248,3000);
		play_tone(331,3000);

		play_tone(95,3000);
		play_tone(104,3000);
		play_tone(131,3000);
		play_tone(176,3000);
		play_tone(234,3000);
		play_tone(303,3000);

		play_tone(90,3000);
		play_tone(98,3000);
		play_tone(124,3000);
		play_tone(166,3000);
		play_tone(221,3000);
		play_tone(295,3000);

		play_tone(85,3000);
		play_tone(93,3000);
		play_tone(117,3000);
		play_tone(156,3000);
		play_tone(209,3000);
		play_tone(279,3000);

	}
	return 0;
}
