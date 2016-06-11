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
		play_tone(113,3000);
		play_tone(124,3000);
		play_tone(156,3000);
		play_tone(209,3000);
		play_tone(279,3000);
		play_tone(372,3000);
	}
	return 0;
}
