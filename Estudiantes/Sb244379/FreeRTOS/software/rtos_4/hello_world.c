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
#include <alt_types.h>
#include <system.h>
/* Standard includes */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <alt_types.h>
#include <unistd.h>
#include <malloc.h>

/* Scheduler includes */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "portmacro.h"
//system & IO
#include <io.h>

#define LED_0_TASK_PRIORITY   (tskIDLE_PRIORITY + 1 )
#define LED_1_TASK_PRIORITY   (tskIDLE_PRIORITY + 2 )
#define LED_2_6_TASK_PRIORITY (tskIDLE_PRIORITY + 3 )
#define LED_7_TASK_PRIORITY   (tskIDLE_PRIORITY + 4 )
#define WRITE_LED_PORT(x) (IOWR(LED_BASE,0,x))
#define READ_LED(x)((IORD(LED_BASE,0)& (1<<x))>>x)
#define READ_LED_PORT (IORD(LED_BASE,0))
#define TOGGLE_LED(x) \
{\
	unsigned char in_led=IORD(LED_BASE,0);\
	unsigned char out_tmp=1<<x;\
	unsigned char out=in_led ^ out_tmp;\
	IOWR(LED_BASE,0,out);\
}

void Tarea_LED0(void *pvParameters) {

	for (;;){
		TOGGLE_LED(0);
		vTaskDelay(500 / portTICK_RATE_MS); //

	}
	vTaskDelete(NULL);
}

void Tarea_LED1(void *pvParameters) {

	for (;;){
		TOGGLE_LED(1);
		vTaskDelay(100 / portTICK_RATE_MS); //

	}
	vTaskDelete(NULL);
}

void Tarea_LED2_6(void *pvParameters) {
	unsigned char led_2_6;
	unsigned char temp_led;
	led_2_6=1;
	for (;;){

		if (led_2_6 & 0x10){
			led_2_6=1;
		}
		led_2_6=led_2_6<<1;
		temp_led=READ_LED_PORT & 0x83;
		temp_led=temp_led | (led_2_6<<2);
		WRITE_LED_PORT(temp_led);

		vTaskDelay(50 / portTICK_RATE_MS); //
	}
	vTaskDelete(NULL);
}

void Tarea_LED7(void *pvParameters) {

	for (;;){
		TOGGLE_LED(7);
		vTaskDelay(1000 / portTICK_RATE_MS); //

		vTaskDelay(45 / portTICK_RATE_MS);
	}
	vTaskDelete(NULL);
}

void SetupHardware(){
	WRITE_LED_PORT(0); //inicia los leds en 0
}
int main() {

	SetupHardware();
	(void) xTaskCreate(Tarea_LED0, (signed portCHAR *) "Terea_LED0",
			configMINIMAL_STACK_SIZE, (void * )0, LED_0_TASK_PRIORITY,
			(xTaskHandle *)NULL);
	(void) xTaskCreate(Tarea_LED1, (signed portCHAR *) "Terea_LED1",
			configMINIMAL_STACK_SIZE, (void * )0, LED_1_TASK_PRIORITY,
			(xTaskHandle *)NULL);
	(void) xTaskCreate(Tarea_LED2_6, (signed portCHAR *) "Terea_LED1",
				configMINIMAL_STACK_SIZE, (void * )0, LED_2_6_TASK_PRIORITY,
				(xTaskHandle *)NULL);
	(void) xTaskCreate(Tarea_LED7, (signed portCHAR *) "Terea_LED1",
					configMINIMAL_STACK_SIZE, (void * )0, LED_7_TASK_PRIORITY,
					(xTaskHandle *)NULL);
	vTaskStartScheduler();

	for (;;) {

	}
	return 0;
}

