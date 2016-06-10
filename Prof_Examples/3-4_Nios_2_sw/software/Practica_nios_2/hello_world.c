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
#include <io.h>
#include <system.h>
#include <unistd.h>


int main()
{
  unsigned char conteo=0;
  unsigned char sw=0;
  while(1){
	  sw=IORD(SW_BASE, 0);
	  if(sw==1){
		  conteo++;
		  IOWR(LEDS_BASE, 0, conteo);
		  printf("conteo = %d\n",conteo);
		  usleep(100000);
	  }
	  else if(sw==2){
		  conteo--;
		  IOWR(LEDS_BASE, 0, conteo);
		  printf("conteo = %d\n",conteo);
		  usleep(100000);
	  }
	  else{
		  conteo=~conteo;
		  IOWR(LEDS_BASE, 0, conteo);
		  printf("conteo = %d\n",conteo);
		  usleep(100000);
	  }
  }

  return 0;
}
