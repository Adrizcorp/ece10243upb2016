/***********************************************************************
*
* Module:  Advanced flashing-LED system using Altera HAL/C stdlib
* File:    chu_main_led2_hal.c
* Purpose: Task routines and main program
*
**********************************************************************/
/* include section */
/* General C library */
#include <stdio.h>
#include <unistd.h>
/* Altera-specific library */
#include "alt_types.h"
#include "system.h"
/* Module-specific library */
#include "chu_avalon_gpio.h"

/***********************************************************************
* data type definitions
***********************************************************************/
typedef struct flash_cmd{
  int pause;
  int prd;
} cmd_type;

/***********************************************************************
* function: flashsys_init_v2()
* purpose:  system initialization
* argument:
*   btn_base: base address of pushbutton PIO
* return:
* note:
***********************************************************************/
void flashsys_init_v2(alt_u32 btn_base)
{
  btn_clear(btn_base);              // clear button edge-capture reg
}

/***********************************************************************
* function: sw_get_command_v1()
* purpose:  get command from pushbuttons and switches
* argument:
*   btn_base: base address of pushbutton PIO
*   sw_base: base address of switch PIO
*   cmd: pointer to command
* return:
*   updated cmd
* note:
***********************************************************************/
void sw_get_command_v1(alt_u32 btn_base, alt_u32 sw_base, cmd_type *cmd)
{
  alt_u8 btn;

  btn = (alt_u8) btn_read(btn_base) & 0xf;    // read 4 pushbuttons
  if (btn!=0){                                // a button pressed
    if (btn & 0x01)                           // button 0 pressed
      cmd->pause = cmd->pause ^ 1;            // toggle pause bit
    if (btn & 0x02)                           // button 1 pressed
      cmd->prd = pio_read(sw_base) & 0x03ff;  // load new interval
    btn_clear(btn_base);                      // clear edge-capture reg
  }
}

/***********************************************************************
* function: jtag_uart_disp_msg_v2()
* purpose:  display the interval when it is changed
* argument:
*   cmd: command
* return:
* note:
***********************************************************************/
void jtag_uart_disp_msg_v2(cmd_type cmd)
{
  static int old=0;

  if (cmd.prd!=old){
    printf("Interval: %03u ms \n", cmd.prd);
    old = cmd.prd;
  }
}

/***********************************************************************
* function: sseg_disp_msg_v1()
* purpose:  display current pause status and interval on 4-digit 7-seg LED
* argument:
*   sseg_base: base address of seven-segment LED display PIO
*   cmd: command
* return:
* note:
***********************************************************************/
void sseg_disp_msg_v1(alt_u32 sseg_base, cmd_type cmd)
{
  int pd;
  alt_u8 hex, msg[4];


  if (cmd.prd > 999)             // 999 is max # to be displayed
    pd = 999;
  else
    pd = cmd.prd;
  hex = pd%10;                   // 0 digit
  msg[3] = sseg_conv_hex(hex);
  hex = (pd/10)%10;              // 10 digit
  msg[2] = sseg_conv_hex(hex);
  hex = pd/100;                  // 100 digit
  msg[1] = sseg_conv_hex(hex);
  /* specify pattern for the most significant digit */
  if (cmd.pause)
    msg[0] = 0x0c;               // P pattern
  else
    msg[0] = 0xff;               // Blank
  sseg_disp_ptn(sseg_base, msg); // display the whole pattern
}

/***********************************************************************
* function: led_flash_v2()
* purpose:
* argument:
*   cmd: command
* return:
* note:
*   The delay is done by continuously checking 1-ms tick
***********************************************************************/
void led_flash_v2(alt_u32 led_base, cmd_type cmd)
{
  static alt_u8 led_pattern = 0x01;

  if (cmd.pause)                         // no toggle if pause asserted
    return;
  led_pattern ^= 0x03;                   // toggle 2 LSBs of LEDs
  pio_write(led_base, led_pattern);      // write LEDs
  usleep(1000*cmd.prd);                  // delay for cmd.prd ms
}

/***********************************************************************
* function: main()
* purpose:  advanced flashing LED system using HAL
* note:
***********************************************************************/
int  main(){
  cmd_type sw_cmd={0,100};  // not pause; 100 ms interval

  flashsys_init_v2(BTN_BASE);
  while(1){
    sw_get_command_v1(BTN_BASE, SWITCH_BASE ,&sw_cmd);
    jtag_uart_disp_msg_v2(sw_cmd);
    sseg_disp_msg_v1(SSEG_BASE, sw_cmd);
    led_flash_v2(LEDG_BASE,sw_cmd);
  }
}

