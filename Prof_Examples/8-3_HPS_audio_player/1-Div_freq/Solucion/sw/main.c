/*
 * ejemplo.c
 *
 *  Created on: Jun 21, 2016
 *      Author: Holguer
 */


#include <stdio.h>
#include <unistd.h>// usleep()
#include <fcntl.h> //
#include <sys/mman.h> //
#include "socal.h"
#include "hps.h"
#include "alt_gpio.h"
#include "hwlib.h"
#include "hps_0.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )


volatile unsigned long *h2p_lw_led_addr=NULL;
volatile unsigned long *h2p_lw_div_addr=NULL;

void set_freq(unsigned int frecuencia){
	if(frecuencia==0){

	}
	else{
	*(unsigned int *)h2p_lw_div_addr=(unsigned int)(50000000/(frecuencia*2))-1;
	}
}


int main(){

	void * virtual_base;
	int fd;

	fd=open("/dev/mem",(O_RDWR | O_SYNC));
	if(fd==-1){
		printf("Failed /dev/mem \n");
		return 0;
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
	        printf( "ERROR: mmap() failed...\n" );
	        close( fd );
	        return( 1 );
	    }

	h2p_lw_led_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + LED_PIO_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	h2p_lw_div_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + DIV_FREQ_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

	//escritura al puerto
	unsigned char leds=0;
	while(1){
		*(unsigned int *)h2p_lw_led_addr = leds;
		set_freq(100*leds);
		leds++;
		usleep(50000);
	}


	return 0;
}
