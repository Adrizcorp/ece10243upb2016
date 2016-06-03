/***********************************************************************
*
* Module:  GCD function prototypes and main
* File:    chu_main_gcd_test.c
* Purpose: software- and hardware-accelerator-based GCD routines
* IP core base addresses:
*    - G_ENGINE_BASE: GCD engine
*
************************************************************************
*  Register map
************************************************************************
* Write (data from cpu):
*   offset 0
*     * bits 31-0: 32-bit a
*   offset 1
*     * bits 31-0: 32-bit b
*   offset 2
*     * dummy data to start operation
* Read (data to cpu):
*   offset 3
*     * bit 32: 1-bit ready signal
*     * bits 15 - 0: 16-bit timer count
*   offset 4
*     * bits 31-0: 32-bit GCD result
***********************************************************************/
/* file inclusion */
/* General C library */
#include <stdio.h>
#include <stdlib.h>   // to use rand()
/* Altera-specific library */
#include <io.h>
#include <alt_types.h>
#include <sys/alt_timestamp.h>
#include "system.h"

/* address and field definition */
#define GCD_A_REG        0
#define GCD_B_REG        1
#define GCD_START_REG    2
#define GCD_STATUS_REG   3
#define GCD_R_REG        4
#define GCD_CNT_FLD      0x0000ffff
#define GCD_READY_BIT    0x80000000

/* macro definition */
#define even(x) (((x) & 1)==0)    // check whether x is an even number

/***********************************************************************
* function: calc_gcd_soft()
* purpose:  calculate GCD by binary GCD algorithm
* argument:
*   a, b: 2 operands of gcd function
*   *ticks: # clock cycles calculated by alt_timestamp() function
* return:
*   - gcd(a,b)
*   - *ticks updated
* note:
*   - call/return/execution of alt_timestamp() introduces extra overhead
*   - use stop_stamp_timer()/start_stamp_timer() to pause the timer to
*     get more accurate result
***********************************************************************/
alt_u32 calc_gcd_soft(alt_u32 a, alt_u32 b, int *ticks)
{
  int n=0;
  alt_32 t0, t1, overhead;

  alt_timestamp_start();        // initialize time_stamp timer to 0
  /* determine the overhead of alt_timestamp() */
  t0 = alt_timestamp();
  t1 = alt_timestamp();
  overhead = t1 - t0;
  /* start actual measurement */
  t0 = alt_timestamp();
   while (1){
    if (a==b)
      break;
    if (even(a)){      // a even
      a = a>>1;
      if (even(b)){    // b even
        b = b>>1;
        n++;
      }
    } else {           // a odd
      if (even(b))     // b even
        b = b>>1;
      else {           // b odd
        if (a > b)
          a = a - b;
        else
          b = b - a;
      } // end else (b odd)
    } // end else (a odd)
  } // end while
  a = a<<n;
  t1 = alt_timestamp();
  *ticks = (int) (t1-t0-overhead);
  return(a);
}

/***********************************************************************
* function: calc_gcd_hard()
* purpose:  calculate GCD via hardware accelerator
* argument:
*   gcd_base: base address of GCD engine
*   a, b: 2 operands of gcd function
*   *clks:  # clock cycles from hardware accelerator
* return:
*   - gcd(a,b)
*   - *clks updated
* note:
***********************************************************************/
alt_u32 calc_gcd_hard(alt_u32 gcd_base, alt_u32 a, alt_u32 b, int *clks)
{
  alt_u32 status, result;

  IOWR(gcd_base, GCD_A_REG, a);     // write a
  IOWR(gcd_base, GCD_B_REG, b);     // write b
  IOWR(gcd_base, GCD_START_REG, 0); // write dummy data to start operation
  while(1){
  /* loop until GCD data is ready */
    status=IORD(gcd_base, GCD_STATUS_REG);
    if (status & GCD_READY_BIT)
      break;
  }
  *clks = (int) (status & GCD_CNT_FLD);
  result=IORD(gcd_base, GCD_R_REG);
  return(result);
}


/***********************************************************************
* function: main()
* purpose:  calculate gcd and collect statistics for randomly selected numbers
*           by software routine and hardware accelerator
* note:
***********************************************************************/
int main(void)
{
  alt_u32 a, b, rs, rh;
  int i;
  int s=0, c=0;
  int samples=10000;
  int s_ticks, clks;

  printf("GCD test:\n\n");
  srand(100);                   // set the random number seed
  for (i=0; i<samples; i++){    // obtain gcd for 10,000 random samples
    a = rand() + 1;             // +1 to avoid 0
    b = rand() + 1;
    rs = calc_gcd_soft(a, b, &s_ticks);
    rh = calc_gcd_hard(G_ENGINE_BASE, a, b, &clks);
    if (rs!=rh)                // sanity check
      printf("Inconsistency: gcd(%d,%d)=%d/%d\n", a, b, rs, rh);
    s = s + s_ticks;
    c = c + clks;
  }
  printf("average clocks (soft/hard): %d/%d\n", s/samples, c/samples);
  printf("hardware accelerator speedup: %d\n", s/c);
}


//#define start_stamp_timer(base) IOWR(base, 1, 0x00000004) // start timer
//#define stop_stamp_timer(base)  IOWR(base, 1, 0x00000008) // pause timer

/*
*  - Use alt_timestamp() introduces extra overhead (~50 cycles) for nios2/f
*  - cannot use alt_nticks() since the interval of n_ticks is usually much larger
*    (defined in Timeout period of system timer, default 1 ms)
*  - ISR may introduce additional clocks for alt_timestamp
*  - The execution of while-loop of calc_gcd_hard() may be longer than the
*    execution time of gcd hardware accelerator and thus the measurement is
*    not accurate
*  - The fmax of gcd hardware accelerator is about 125 MHz and
*    its performance can be further increased by using a pll
*  - alt_timestamp_type can be 32- or 64-bit unsigned integer,
*    determined by teh width of time-stamp timer
*  - RAND_MAX (max of rand() is 0x7fffffff
*/