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

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "io.h"
#include "system.h"
#include "includes.h"

#define do 95565
#define re 85129
#define mi 75842
#define fa 71585
#define sol 63775
#define sols 60230
#define la 56817
#define las 54935
#define si 50619
#define doh 47791
#define dosh 45116
#define reh 37935
#define resh 40191
#define mih 37935
#define fah 35815
#define fash 33782
#define solh 31886
#define solsh 30119
#define lah 28408
#define dom 47777
#define rem 42565
#define mim 37920
#define fam 35792
#define solm 31887
#define lam 28408
#define sim 25309

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
			printf("Hola jesus_lopez ++\n");
			IOWR(LEDS_BASE,0,counter);
			counter++;
			OSTimeDlyHMSM(0, 0, 0, 100);
		  }
		  else{
			printf("Hola jesus_lopez --\n");
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


			  play_tone(la, 500);
			  	play_tone(la, 500);
			  	play_tone(la, 500);
			  	play_tone(fa, 350);
			  	play_tone(doh, 150);

			  	play_tone(la, 500);
			  	play_tone(fa, 350);
			  	play_tone(doh, 150);
			  	play_tone(la, 1000);
			  	//first bi

			  	play_tone(mih, 500);
			  	play_tone(mih, 500);
			  	play_tone(mih, 500);
			  	play_tone(fah, 350);
			  	play_tone(doh, 150);

			  	play_tone(sols, 500);
			  	play_tone(fa, 350);
			  	play_tone(doh, 150);
			  	play_tone(la, 1000);
			  	//second b..

			  	play_tone(lah, 500);
			  	play_tone(la, 350);
			  	play_tone(la, 150);
			  	play_tone(lah, 500);
			  	play_tone(solsh, 250);
			  	play_tone(solh, 250);

			  	play_tone(fash, 125);
			  	play_tone(fah, 125);
			  	play_tone(fash, 250);
			  	play_tone(silence,250);
			  	play_tone(las, 250);
			  	play_tone(resh, 500);
			  	play_tone(reh, 250);
			  	play_tone(dosh, 250);
			  	//start of the interesting bit

			  	play_tone(doh, 125);
			  	play_tone(si, 125);
			  	play_tone(doh, 250);
			  	play_tone(silence,250);
			  	play_tone(fa, 125);
			  	play_tone(sols, 500);
			  	play_tone(fa, 375);
			  	play_tone(la, 125);

			  	play_tone(doh, 500);
			  	play_tone(la, 375);
			  	play_tone(doh, 125);
			  	play_tone(mih, 1000);
			  	//more interesting stuff (this doesn't quite get it right somehow)

			  	play_tone(lah, 500);
			  	play_tone(la, 350);
			  	play_tone(la, 150);
			  	play_tone(lah, 500);
			  	play_tone(solsh, 250);
			  	play_tone(solh, 250);

			  	play_tone(fash, 125);
			  	play_tone(fah, 125);
			  	play_tone(fash, 250);
			  	play_tone(silence,250);
			  	play_tone(las, 250);
			  	play_tone(resh, 500);
			  	play_tone(reh, 250);
			  	play_tone(dosh, 250);
			  	//repeat... repeat

			  	play_tone(doh, 125);
			  	play_tone(si, 125);
			  	play_tone(doh, 250);
			  	play_tone(silence,250);
			  	play_tone(fa, 250);
			  	play_tone(sols, 500);
			  	play_tone(fa, 375);
			  	play_tone(doh, 125);

			  	play_tone(la, 500);
			  	play_tone(fa, 375);
			  	play_tone(do, 125);
			  	play_tone(la, 1000);
			  	play_tone(silence,400);
		  }
}
void leds_task(void* pdata)
{

  while (1)
  {
	    play_tone1(do,400);
		play_tone1(fa,200);
		play_tone1(fa,200);
		play_tone1(fa,600);
		play_tone1(sol,400);
		play_tone1(la,200);
		play_tone1(la,200);
		play_tone1(la,600);
		play_tone1(la,200);
		play_tone1(sol,200);
		play_tone1(sol,200);
		play_tone1(si,600);
		play_tone1(mi,400);
		play_tone1(sol,400);
		play_tone1(fa,1000);
		play_tone1(do,400);
		play_tone1(fa,200);
		play_tone1(fa,200);
		play_tone1(fa,600);
		play_tone1(sol,400);
		play_tone1(la,200);
		play_tone1(la,200);
		play_tone1(la,600);
		play_tone1(la,200);
		play_tone1(sol,200);
		play_tone1(la,200);
		play_tone1(si,600);
		play_tone1(mi,400);
		play_tone1(sol,400);
		play_tone1(fa,1000);
		//
		play_tone1(do,200);
		play_tone1(do,200);
		play_tone1(la,200);
		play_tone1(rem,400);
		play_tone1(dom,200);
		play_tone1(dom,200);
		play_tone1(si,200);
		play_tone1(si,400);
		play_tone1(si,200);
		play_tone1(si,200);
		play_tone1(sol,200);
		play_tone1(dom,400);
		play_tone1(si,200);
		play_tone1(si,200);
		play_tone1(la,200);
		play_tone1(la,400);
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
