/***********************************************************************
*
* Module:  Demo timer driver functions
* File:    chu_timer_drv.c
* Purpose: Functions to set up timer
*
***********************************************************************/
/* file inclusion */
#include "chu_timer_drv.h"

/***********************************************************************
* function: timer_wr_prd()
* purpose:  write timer timeout period and configure/start timer
* argument:
*   timer_base: base address of time-stamp timer
*   prd: timeout period value
* return:
* note:
***********************************************************************/
void timer_wr_prd(alt_u32 timer_base, alt_u32 prd)
{
  alt_u16 high, low;

  /* unpack 32-bit timeout period into two 16-bit half words */
  high = (alt_u16) (prd>>16);
  low = (alt_u16) (prd & 0x0000ffff);
  /* write timeout period */
  IOWR(timer_base, TIMER_PRDH_REG_OFT, high);
  IOWR(timer_base, TIMER_PRDL_REG_OFT, low);
  /* configure timer to start, continuous mode; enable interrupt */
  IOWR(timer_base, TIMER_CTRL_REG_OFT, 0x0007);
}

