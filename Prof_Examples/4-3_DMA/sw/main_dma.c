/*
 * main_dma.c
 *
 *  Created on: Jun 16, 2016
 *      Author: Holguer
 */

#include <stdio.h>
#include <io.h>
#include <altera_avalon_sgdma.h>
#include <altera_avalon_sgdma_descriptor.h>
#include <altera_avalon_sgdma_regs.h>


// DMA descriptors
alt_sgdma_descriptor dmaDescA[8];
alt_sgdma_descriptor dmaDescEND;

int main(){
	unsigned int vector[5]={0x00010203,0x04050607,0x08090A0B,0x0C0D0E0F,0x10111213};
	 // initialize the DMA and get a device handle
	alt_sgdma_dev *dma_out = alt_avalon_sgdma_open("/dev/sgdma_out");

	//modificicacion de Descriptores
	 unsigned char * buff;
	 buff=(unsigned char *)&vector[0];
	 unsigned short size = 5*sizeof(unsigned int);// 5 DWORDS


    while(1){
    	printf("Building descriptors...\n");
    	//construye el descriptor de datos q van a
    	//ser enviados
    	alt_avalon_sgdma_construct_mem_to_stream_desc(
    	            &dmaDescA[0],
    	            &dmaDescEND,
    	            (alt_u32*)buff,
    	            size,
    	            0,
    	            1,
    	            1,
    	            0);
    	printf("Sending Data through DMA channel\n");
       // envia de manera sincrona los datos por medio del DMA
    	alt_avalon_sgdma_do_sync_transfer(dma_out, dmaDescA);

    	printf("Delay... 1 Sec before going ahead\n");
    	// delay
    	usleep(1000000);

    }


	return 0;
}


