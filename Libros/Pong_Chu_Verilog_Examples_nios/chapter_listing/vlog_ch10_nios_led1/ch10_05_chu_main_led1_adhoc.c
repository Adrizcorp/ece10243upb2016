/***********************************************************************
*
* Module:  Simple flashing-LED system
* File:    chu_main_led1_adhoc.c
* Purpose: Flashes two LEDs alternatively
*          and uses 10 slide switches to set the flashing period
*
***********************************************************************/
#include "io.h"
#include "alt_types.h"
#include "system.h"


/***********************************************************************
* function: sw_get_command_v0()
* purpose:  get flashing period from switches
* argument:
*   sw_base: base address of switch PIO
*   prd: pointer to period
* return:
*   updated prd
* note:
***********************************************************************/
void sw_get_command_v0(alt_u32 sw_base, int *prd)
{
  *prd = IORD(sw_base, 0) & 0x000003ff;  // read flashing period
}

/***********************************************************************
* function: led_flash_v0()
* purpose:  toggle 2 LEDs according to the given period
* argument:
*   led_base: base address of discrete LED PIO
*   prd: flashing period in ms
* return:
* note:
*   - The delay is done by estimating execution time of a dummy for loop
*   - Assumption: 400 ns per loop iteration (2500 iterations per ms)
*     - 2 instructions per loop iteration
*     - 10 clock cycles per instruction
*     - 20 ns per clock cycle (50-MHz clock)
***********************************************************************/
void led_flash_v0(alt_u32 led_base, int prd)
{
  static alt_u8 led_pattern = 0x01;    // initial pattern
  unsigned long i, itr;

  led_pattern ^= 0x03;                 // toggle 2 LEDs (2 LSBs)
  IOWR(led_base, 0, led_pattern);      // write LEDs
  itr = prd * 2500;
  for (i=0; i<itr; i ++){}             // dummy loop for delay
}

/***********************************************************************
* function: main()
* purpose:  top-level program
* note:
***********************************************************************/
int main(){
  int prd;

  while(1){
    sw_get_command_v0(SWITCH_BASE ,&prd);
    led_flash_v0(LED_BASE, prd);
  }
}



