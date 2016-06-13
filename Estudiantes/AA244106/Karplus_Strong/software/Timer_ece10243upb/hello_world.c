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
#include <io.h> //para acceder a perifericos
#include <sys/alt_irq.h> //para interrupciones
#include <system.h>

void initTimer(int frequency){
	int in_div_freq=(50000000/(2*frequency))-1;
	IOWR(TIMER_ECE10243UPB2016_0_BASE, 0, in_div_freq);
}

void clr_timer_irq(){
	IOWR(TIMER_ECE10243UPB2016_0_BASE, 1, 0);
}

static void timer_isr(void * context){
	//el proceso que llama la interrupcion
	static unsigned short counter = 0;
	IOWR(LEDS_BASE, 0, counter);
	counter++;
	printf("Llego a la interrupcion\n");
	//debe hacer clear de la interrupcion
	clr_timer_irq();
}


int main()
{
	initTimer(1); //1Hz
	//registra la interrupcion y ata a la funcion timer_isr
	alt_ic_isr_register(TIMER_ECE10243UPB2016_0_IRQ_INTERRUPT_CONTROLLER_ID,TIMER_ECE10243UPB2016_0_IRQ,timer_isr,(void*)NULL, 0);
	alt_ic_irq_enable (TIMER_ECE10243UPB2016_0_IRQ_INTERRUPT_CONTROLLER_ID,TIMER_ECE10243UPB2016_0_IRQ);
	while(1){

	}

  return 0;
}


//Tarea ¿por qué sólo interrumpe una vez?, hacer que interrumpa con cada flanco del reloj
