/*
 * main.c
 *
 *  Created on: Jun 20, 2016
 *      Author: Holguer
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "socal.h"
#include "hps.h"
#include "alt_gpio.h"
#include "hwlib.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

#define USER_IO_DIR     (0x01000000)
#define BIT_LED         (0x01000000)
#define BUTTON_MASK     (0x02000000)

#define LED_SET()	alt_setbits_word( ( virtual_base + ( ( uint32_t )( ALT_GPIO1_SWPORTA_DR_ADDR ) & ( uint32_t )( HW_REGS_MASK ) ) ), BIT_LED )
#define LED_CLR()   alt_clrbits_word( ( virtual_base + ( ( uint32_t )( ALT_GPIO1_SWPORTA_DR_ADDR ) & ( uint32_t )( HW_REGS_MASK ) ) ), BIT_LED )
#define READ_KEY()  alt_read_word( ( virtual_base + ( ( uint32_t )(  ALT_GPIO1_EXT_PORTA_ADDR ) & ( uint32_t )( HW_REGS_MASK ) ) ) )


int main(int argc, char **argv) {

	void *virtual_base;
	int fd;
	uint32_t  scan_input;
	int i;
	// map the address space for the LED registers into user space so we can interact with them.
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return( 1 );
	}
	// initialize the pio controller
	// led: set the direction of the HPS GPIO1 bits attached to LEDs to output
	alt_setbits_word( ( virtual_base + ( ( uint32_t )( ALT_GPIO1_SWPORTA_DDR_ADDR ) & ( uint32_t )( HW_REGS_MASK ) ) ), USER_IO_DIR );


	int numero_flashes=0;
	int delay=100;

	if(argc>1){
		sscanf (argv[1],"%d",&numero_flashes);
		if(argc>2){
			sscanf (argv[2],"%d",&delay);
		}

	}
	else {
		printf("Please use the next input style: ./%s #flashes\n",argv[0]);
		printf("or use the next input style: ./%s #flashes delay\n",argv[0]);
		return 0;
	}

	printf("led test\r\n");
	printf("the led flashes %d times\r\n",numero_flashes);
	for(i=0;i<numero_flashes;i++)
	{
		LED_SET();
		usleep(delay*1000);
		LED_CLR();
		usleep(delay*1000);
	}
	/*printf("user key test \r\n");
	printf("press key to control led\r\n");
	while(1){
		scan_input =READ_KEY();
		//usleep(1000*1000);
		if(~scan_input&BUTTON_MASK){
			LED_SET();
		}
		else{
			LED_CLR();
			}
	}*/

	// clean up our memory mapping and exit
	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}
	close( fd );
	return( 0 );
}
