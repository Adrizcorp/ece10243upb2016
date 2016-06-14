/*************************************************************************
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
**************************************************************************
* Description:                                                           *
* The following is a simple hello world program running MicroC/OS-II.The * 
* purpose of the design is to be a very simple application that just     *
* demonstrates MicroC/OS-II running on NIOS II.The design doesn't account*
* for issues such as checking system call return codes. etc.             *
*                                                                        *
* Requirements:                                                          *
*   -Supported Example Hardware Platforms                                *
*     Standard                                                           *
*     Full Featured                                                      *
*     Low Cost                                                           *
*   -Supported Development Boards                                        *
*     Nios II Development Board, Stratix II Edition                      *
*     Nios Development Board, Stratix Professional Edition               *
*     Nios Development Board, Stratix Edition                            *
*     Nios Development Board, Cyclone Edition                            *
*   -System Library Settings                                             *
*     RTOS Type - MicroC/OS-II                                           *
*     Periodic System Timer                                              *
*   -Know Issues                                                         *
*     If this design is run on the ISS, terminal output will take several*
*     minutes per iteration.                                             *
**************************************************************************/


#include <stdio.h>
#include "includes.h"
#include <system.h>
#include <io.h>
#define c4 95565
#define d4 85129
#define e4 75842
#define f4 71585
#define g4 63775
#define a4 56817
#define b4 50619
#define c5 47777
#define d5 42565
#define e5 37920
#define f5 35792
#define g5 31887
#define a5 28408
#define b5 25309
#define silence 1

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];
OS_STK    leds_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2
#define LEDS_PRIORITY       3

void play_tone(int nota, int time_ms){
	IOWR(DIV_FREQ_BASE,0,nota);
	OSTimeDlyHMSM(0, 0, 0, time_ms*2);
	IOWR(DIV_FREQ_BASE,0,silence);
	OSTimeDlyHMSM(0, 0, 0, 10);
}
void play_tone1(int nota, int time_ms){
	IOWR(DIV_FREQ1_BASE,0,nota);
	OSTimeDlyHMSM(0, 0, 0, time_ms*2);
	IOWR(DIV_FREQ1_BASE,0,silence);
	OSTimeDlyHMSM(0, 0, 0, 10);
}
/* Prints "Hello World" and sleeps for three seconds */
void task1(void* pdata)
{
	unsigned char counter=0;
	  while (1)
	  {
		  int est= IORD(SW_BASE,0);
		//  counter= IORD(LEDS_BASE,0);
		  if(est==0){
			printf("Hola led ++\n");
			IOWR(LEDS_BASE,0,counter);
			counter++;
			OSTimeDlyHMSM(0, 0, 0, 100);
		  }
		  else{
			printf("Hola led --\n");
			IOWR(LEDS_BASE,0,counter);
			counter--;
			OSTimeDlyHMSM(0, 0, 0, 100);

		  }
	  }
}
/* Prints "Hello World" and sleeps for three seconds */
void task2(void* pdata)
{

		  while (1)
		  {


			  play_tone(b4,400);

			    play_tone(c5,200);

			    play_tone(d5,200);

			    play_tone(d5,200);

			    play_tone(c5,200);

			    play_tone(b4,200);

			    play_tone(a4,200);

			    play_tone(g4,200);

			    play_tone(g4,200);

			    play_tone(a4,200);

			    play_tone(b4,200);

			    play_tone(b4,300);

			    play_tone(a4,100);

			    play_tone(a4,400);

			    play_tone(b4,400);

			    play_tone(c5,200);

			    play_tone(d5,200);

			    play_tone(d5,200);

			    play_tone(c5,200);

			    play_tone(b4,200);

			    play_tone(a4,200);

			    play_tone(g4,200);

			    play_tone(g4,200);

			    play_tone(a4,200);

			    play_tone(b4,200);

			    play_tone(a4,300);

			    play_tone(g4,100);

			    play_tone(g4,400);
			    play_tone(silence,200);
			    play_tone(a4,400);
			    play_tone(b4,200);
			    play_tone(g4,200);
			    play_tone(a4,200);
			    play_tone(b4,100);
			    play_tone(c5,100);
			    play_tone(b4,200);
			    play_tone(g4,200);
			    play_tone(a4,200);
			    play_tone(b4,100);
			    play_tone(c5,100);
			    play_tone(b4,200);
			    play_tone(a4,200);
			    play_tone(g4,200);
			    play_tone(a4,200);
			    play_tone(d4,400);
			    play_tone(b4,400);
			    play_tone(c5,200);
			    play_tone(d5,200);
			    play_tone(d5,200);
			    play_tone(c5,200);
			    play_tone(b4,200);
			    play_tone(a4,200);
			    play_tone(g4,200);
			    play_tone(g4,200);
			    play_tone(a4,200);
			    play_tone(b4,200);
			    play_tone(a4,300);
			    play_tone(g4,100);
			    play_tone(g4,400);
			    play_tone(silence,400);

		  }
}
void leds_task(void* pdata)
{

  while (1)
  {
	    play_tone1(c4,400);
		play_tone1(f4,200);
		play_tone1(f4,200);
		play_tone1(f4,600);
		play_tone1(g4,400);
		play_tone1(a4,200);
		play_tone1(a4,200);
		play_tone1(a4,600);
		play_tone1(a4,200);
		play_tone1(g4,200);
		play_tone1(a4,200);
		play_tone1(b4,600);
		play_tone1(e4,400);
		play_tone1(g4,400);
		play_tone1(f4,1000);
		play_tone1(c4,400);
		play_tone1(f4,200);
		play_tone1(f4,200);
		play_tone1(f4,600);
		play_tone1(g4,400);
		play_tone1(a4,200);
		play_tone1(a4,200);
		play_tone1(a4,600);
		play_tone1(a4,200);
		play_tone1(g4,200);
		play_tone1(a4,200);
		play_tone1(b4,600);
		play_tone1(e4,400);
		play_tone1(g4,400);
		play_tone1(f4,1000);
		//
		play_tone1(c5,200);
		play_tone1(c5,200);
		play_tone1(a4,200);
		play_tone1(d5,400);
		play_tone1(c5,200);
		play_tone1(c5,200);
		play_tone1(b4,200);
		play_tone1(b4,400);
		play_tone1(b4,200);
		play_tone1(b4,200);
		play_tone1(g4,200);
		play_tone1(c5,400);
		play_tone1(b4,200);
		play_tone1(b4,200);
		play_tone1(a4,200);
		play_tone1(a4,400);
  }
}
/* The main function creates two task and starts multi-tasking */
int main(void)
{
  
  OSTaskCreateExt(task1,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE-1],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
              
               
  OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE-1],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  OSTaskCreateExt(leds_task,
                   NULL,
                   (void *)&leds_stk[TASK_STACKSIZE-1],
                   LEDS_PRIORITY,
                   LEDS_PRIORITY,
                   leds_stk,
                   TASK_STACKSIZE,
                   NULL,
                   0);
  OSStart();
  return 0;
}

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/
