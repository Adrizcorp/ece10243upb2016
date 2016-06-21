/*
 * freeRTOScheck.c
 *
 *  Created on: 25/04/2014
 *      Author: AdriZcorp
 */
/* Scheduler includes. */
#include "FreeRTOS.h"
// agregar tareas
#include "task.h"
#include "queue.h"
#include "portmacro.h"
#include <stdio.h>


#define mainNO_ERROR_PERIOD ( 5000 )
/* The parameters passed to the reg test tasks.  This is just done to check
the parameter passing mechanism is working correctly. */
#define mainREG_TEST_1_PARAMETER    ( ( void * ) ONCHIP_MEMORY2_BASE+ONCHIP_MEMORY2_SPAN-1)
#define mainREG_TEST_2_PARAMETER    ( ( void * ) ONCHIP_MEMORY2_BASE+ONCHIP_MEMORY2_SPAN )

/* The rate at which the LED controlled by the 'check' task will toggle when an
error has been detected. */
#define mainERROR_PERIOD    ( 500 )


/* Counters that are incremented on each iteration of the RegTest tasks
so long as no errors have been detected. */
volatile unsigned long ulRegTest1Counter = 0UL, ulRegTest2Counter = 0UL;




void vApplicationStackOverflowHook( void )
{
	/* Look at pxCurrentTCB to see which task overflowed its stack. */
	for( ;; )
    {
		asm( "break" );
    }
}
/*-----------------------------------------------------------*/

void _general_exception_handler( unsigned long ulCause, unsigned long ulStatus )
{
	/* This overrides the definition provided by the kernel.  Other exceptions
	should be handled here. */
	for( ;; )
    {
		asm( "break" );
    }
}
/*-----------------------------------------------------------*/

static void prvCheckTask( void *pvParameters )
{
portTickType xLastExecutionTime, ulTicksToWait = mainNO_ERROR_PERIOD;
unsigned long ulLastRegTest1 = 0UL, ulLastRegTest2 = 0UL;
const char * pcMessage;

	/* Initialise the variable used to control our iteration rate prior to
	its first use. */
	xLastExecutionTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Wait until it is time to run the tests again. */
		vTaskDelayUntil( &xLastExecutionTime, ulTicksToWait );

		/* Have any of the standard demo tasks detected an error in their
		operation? */
		if( ulLastRegTest1 == ulRegTest1Counter )
        {
            /* ulRegTest1Counter is no longer being incremented, indicating
            that an error has been discovered in prvFirstRegTestTask(). */
            ulTicksToWait = mainERROR_PERIOD;
            pcMessage = "Error: Reg Test1.\n";
        }
        else if( ulLastRegTest2 == ulRegTest2Counter )
        {
            /* ulRegTest2Counter is no longer being incremented, indicating
            that an error has been discovered in prvSecondRegTestTask(). */
            ulTicksToWait = mainERROR_PERIOD;
            pcMessage = "Error: Reg Test2.\n";
        }
		else
		{
			pcMessage = NULL;
		}

        /* Remember the counter values this time around so a counter failing
        to be incremented correctly can be spotted. */
        ulLastRegTest1 = ulRegTest1Counter;
        ulLastRegTest2 = ulRegTest2Counter;

        /* Print out an error message if there is one.  Mutual exclusion is
        not used as this is the only task accessing stdout. */
        if( pcMessage != NULL )
        {
            printf( pcMessage );
        }


        //added cjr
        printf(".");
	}
}
/*-----------------------------------------------------------*/

static void prvFirstRegTestTask( void *pvParameters )
{
    /* Check the parameters are passed in as expected. */
    if( pvParameters != mainREG_TEST_1_PARAMETER )
    {
        /* Don't execute any further so an error is recognised by the check
        task. */
        vTaskDelete( NULL );
    }

    /* Fill registers with known values, then check that each register still
    contains its expected value.  An incorrect value is indicative of an error
    in the context switching process.

    If no errors are found ulRegTest1Counter is incremented.  The check task
    will recognise an error if ulRegTest1Counter stops being incremented.
    This task also performs a manual yield in the middle of its execution, just
    to increase the test coverage. */
    asm volatile (
        "   .extern ulRegTest1Counter           \n" \
        "                                       \n" \
        "   addi    r3, r0, 3                   \n" \
        "   addi    r4, r0, 4                   \n" \
        "   addi    r5, r0, 5                   \n" \
        "   addi    r6, r0, 6                   \n" \
        "   addi    r7, r0, 7                   \n" \
        "   addi    r8, r0, 8                   \n" \
        "   addi    r9, r0, 9                   \n" \
        "   addi    r10, r0, 10                   \n" \
        "   addi    r11, r0, 11                   \n" \
        "   addi    r12, r0, 12                   \n" \
        "   addi    r13, r0, 13                   \n" \
        "   addi    r14, r0, 14                   \n" \
        "   addi    r15, r0, 15                   \n" \
        "   addi    r16, r0, 16                   \n" \
        "   addi    r17, r0, 17                   \n" \
        "   addi    r18, r0, 18                   \n" \
        "   addi    r19, r0, 19                   \n" \
        "   addi    r20, r0, 20                   \n" \
        "   addi    r21, r0, 21                   \n" \
        "   addi    r22, r0, 22                   \n" \
        "   addi    r23, r0, 23                   \n" \
        "   addi    r28, r0, 28                   \n" \
        "   addi    r31, r0, 31                   \n" \
        "RegTest1:                              \n" \
        "   addi    r2, r0, 0                   \n" \
        "   trap                                \n" \
        "   bne     r2, r0, RegTest1Error       \n" \
        "   addi    r2, r0, 3                   \n" \
        "   bne     r2, r3, RegTest1Error       \n" \
        "   addi    r2, r0, 4                   \n" \
        "   bne     r2, r4, RegTest1Error       \n" \
        "   addi    r2, r0, 5                   \n" \
        "   bne     r2, r5, RegTest1Error       \n" \
        "   addi    r2, r0, 6                   \n" \
        "   bne     r2, r6, RegTest1Error       \n" \
        "   addi    r2, r0, 7                   \n" \
        "   bne     r2, r7, RegTest1Error       \n" \
        "   addi    r2, r0, 8                   \n" \
        "   bne     r2, r8, RegTest1Error       \n" \
        "   addi    r2, r0, 9                   \n" \
        "   bne     r2, r9, RegTest1Error       \n" \
        "   addi    r2, r0, 10                   \n" \
        "   bne     r2, r10, RegTest1Error       \n" \
        "   addi    r2, r0, 11                   \n" \
        "   bne     r2, r11, RegTest1Error       \n" \
        "   addi    r2, r0, 12                   \n" \
        "   bne     r2, r12, RegTest1Error       \n" \
        "   addi    r2, r0, 13                   \n" \
        "   bne     r2, r13, RegTest1Error       \n" \
        "   addi    r2, r0, 14                   \n" \
        "   bne     r2, r14, RegTest1Error       \n" \
        "   addi    r2, r0, 15                   \n" \
        "   bne     r2, r15, RegTest1Error       \n" \
        "   addi    r2, r0, 16                   \n" \
        "   bne     r2, r16, RegTest1Error       \n" \
        "   addi    r2, r0, 17                   \n" \
        "   bne     r2, r17, RegTest1Error       \n" \
        "   addi    r2, r0, 18                   \n" \
        "   bne     r2, r18, RegTest1Error       \n" \
        "   addi    r2, r0, 19                   \n" \
        "   bne     r2, r19, RegTest1Error       \n" \
        "   addi    r2, r0, 20                   \n" \
        "   bne     r2, r20, RegTest1Error       \n" \
        "   addi    r2, r0, 21                   \n" \
        "   bne     r2, r21, RegTest1Error       \n" \
        "   addi    r2, r0, 22                   \n" \
        "   bne     r2, r22, RegTest1Error       \n" \
        "   addi    r2, r0, 23                   \n" \
        "   bne     r2, r23, RegTest1Error       \n" \
        "   addi    r2, r0, 28                   \n" \
        "   bne     r2, r28, RegTest1Error       \n" \
        "   addi    r2, r0, 31                   \n" \
        "   bne     r2, r31, RegTest1Error       \n" \
        "   ldw     r2, %gprel(ulRegTest1Counter)(gp)       \n" \
        "   addi    r2, r2, 1                   \n" \
        "   stw     r2, %gprel(ulRegTest1Counter)(gp)       \n" \
        "   br      RegTest1                    \n" \
        "RegTest1Error:                         \n" \
        "   br      RegTest1Error               \n"
    );
}
/*-----------------------------------------------------------*/

static void prvSecondRegTestTask( void *pvParameters )
{
    /* Check the parameters are passed in as expected. */
    if( pvParameters != mainREG_TEST_2_PARAMETER )
    {
        /* Don't execute any further so an error is recognised by the check
        task. */
        vTaskDelete( NULL );
    }

    /* Fill registers with known values, then check that each register still
    contains its expected value.  An incorrect value is indicative of an error
    in the context switching process.

    If no errors are found ulRegTest2Counter is incremented.  The check task
    will recognise an error if ulRegTest2Counter stops being incremented. */
    asm volatile (
        "   .extern ulRegTest2Counter           \n" \
        "                                       \n" \
        "   addi    r3, r0, 3                   \n" \
        "   addi    r4, r0, 4                   \n" \
        "   addi    r5, r0, 5                   \n" \
        "   addi    r6, r0, 6                   \n" \
        "   addi    r7, r0, 7                   \n" \
        "   addi    r8, r0, 8                   \n" \
        "   addi    r9, r0, 9                   \n" \
        "   addi    r10, r0, 10                   \n" \
        "   addi    r11, r0, 11                   \n" \
        "   addi    r12, r0, 12                   \n" \
        "   addi    r13, r0, 13                   \n" \
        "   addi    r14, r0, 14                   \n" \
        "   addi    r15, r0, 15                   \n" \
        "   addi    r16, r0, 16                   \n" \
        "   addi    r17, r0, 17                   \n" \
        "   addi    r18, r0, 18                   \n" \
        "   addi    r19, r0, 19                   \n" \
        "   addi    r20, r0, 20                   \n" \
        "   addi    r21, r0, 21                   \n" \
        "   addi    r22, r0, 22                   \n" \
        "   addi    r23, r0, 23                   \n" \
        "   addi    r28, r0, 28                   \n" \
        "   addi    r31, r0, 31                   \n" \
        "RegTest2:                              \n" \
        "   addi    r2, r0, 0                   \n" \
        "   bne     r2, r0, RegTest2Error       \n" \
        "   addi    r2, r0, 3                   \n" \
        "   bne     r2, r3, RegTest2Error       \n" \
        "   addi    r2, r0, 4                   \n" \
        "   bne     r2, r4, RegTest2Error       \n" \
        "   addi    r2, r0, 5                   \n" \
        "   bne     r2, r5, RegTest2Error       \n" \
        "   addi    r2, r0, 6                   \n" \
        "   bne     r2, r6, RegTest2Error       \n" \
        "   addi    r2, r0, 7                   \n" \
        "   bne     r2, r7, RegTest2Error       \n" \
        "   addi    r2, r0, 8                   \n" \
        "   bne     r2, r8, RegTest2Error       \n" \
        "   addi    r2, r0, 9                   \n" \
        "   bne     r2, r9, RegTest2Error       \n" \
        "   addi    r2, r0, 10                   \n" \
        "   bne     r2, r10, RegTest2Error       \n" \
        "   addi    r2, r0, 11                   \n" \
        "   bne     r2, r11, RegTest2Error       \n" \
        "   addi    r2, r0, 12                   \n" \
        "   bne     r2, r12, RegTest2Error       \n" \
        "   addi    r2, r0, 13                   \n" \
        "   bne     r2, r13, RegTest2Error       \n" \
        "   addi    r2, r0, 14                   \n" \
        "   bne     r2, r14, RegTest2Error       \n" \
        "   addi    r2, r0, 15                   \n" \
        "   bne     r2, r15, RegTest2Error       \n" \
        "   addi    r2, r0, 16                   \n" \
        "   bne     r2, r16, RegTest2Error       \n" \
        "   addi    r2, r0, 17                   \n" \
        "   bne     r2, r17, RegTest2Error       \n" \
        "   addi    r2, r0, 18                   \n" \
        "   bne     r2, r18, RegTest2Error       \n" \
        "   addi    r2, r0, 19                   \n" \
        "   bne     r2, r19, RegTest2Error       \n" \
        "   addi    r2, r0, 20                   \n" \
        "   bne     r2, r20, RegTest2Error       \n" \
        "   addi    r2, r0, 21                   \n" \
        "   bne     r2, r21, RegTest2Error       \n" \
        "   addi    r2, r0, 22                   \n" \
        "   bne     r2, r22, RegTest2Error       \n" \
        "   addi    r2, r0, 23                   \n" \
        "   bne     r2, r23, RegTest2Error       \n" \
        "   addi    r2, r0, 28                   \n" \
        "   bne     r2, r28, RegTest2Error       \n" \
        "   addi    r2, r0, 31                   \n" \
        "   bne     r2, r31, RegTest2Error       \n" \
        "   ldw     r2, %gprel(ulRegTest2Counter)(gp)       \n" \
        "   addi    r2, r2, 1                   \n" \
        "   stw     r2, %gprel(ulRegTest2Counter)(gp)       \n" \
        "   br      RegTest2                    \n" \
        "RegTest2Error:                         \n" \
        "   br      RegTest2Error               \n"
    );
}
/*-----------------------------------------------------------*/

