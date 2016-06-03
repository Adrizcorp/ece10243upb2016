/***********************************************************************
*
* Module:  Advanced flashing-LED system using ad hoc driver
* File:    chu_main_led2_adhoc.c
* Purpose: Task routines and main program
*
***********************************************************************/
/* file inclusion */
#include "system.h"
#include "chu_avalon_gpio.h"
#include "chu_uart_drv.h"
#include "chu_timer_drv.h"

/***********************************************************************
* data type definitions
***********************************************************************/
typedef struct flash_cmd{
  int pause;
  int prd;
} cmd_type;

/***********************************************************************
* function: flashsys_init_v1()
* purpose:  system initialization
* argument:
*   btn_base: base address of pushbutton PIO
*   timer_base: base address of user timer
* return:
* note:
***********************************************************************/
void flashsys_init_v1(alt_u32 btn_base, alt_u32 timer_base)
{
  btn_clear(btn_base);              // clear button edge-capture reg
  timer_wr_prd(timer_base, 50000);  // set 1-ms timeout period
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
* function: jtag_uart_disp_msg_v1()
* purpose:  display the interval when it is changed
* argument:
*   jtag_base: base address of JTAG UART
*   cmd: command
* return:
* note:
***********************************************************************/
void jtaguart_disp_msg_v1(alt_u32 jtag_base, cmd_type cmd)
{
  static int current=0;                // current interval
  char msg[] ="Interval: 0000 ms\n";

  if (cmd.prd!=current){               // new interval detected
    msg[13] = cmd.prd%10 + '0';        // ascii code for 0 digit
    msg[12] = (cmd.prd/10)%10 + '0';   // ascii code for 10 digit
    msg[11] = (cmd.prd/100)%10 + '0';  // ascii code for 100 digit
    msg[10] = cmd.prd/1000 + '0';      // ascii code for 1000 digit
    jtaguart_wr_str(jtag_base, msg);   // send string to console
    current = cmd.prd;                 // update current interval
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
* function: led_flash_v1()
* purpose:  toggle 2 LEDs according to the given interval
* argument:
*   led_base: base address of discrete LED  PIO
*   timer_base: base address of user timer
*   cmd: command
* return:
* note:
*   The delay is done by continuously checking 1 ms tick
***********************************************************************/
void led_flash_v1(alt_u32 led_base, alt_u32 timer_base, cmd_type cmd)
{
  static alt_u8 led_pattern = 0x01;
  int ntick=0;

  if (cmd.pause)                         // no toggle if pause asserted
    return;
  led_pattern ^= 0x03;                   // toggle 2 LSBs of LEDs
  pio_write(led_base, led_pattern);      // write LEDs
  while (ntick < cmd.prd){
    if (timer_read_tick(timer_base)==1){
      timer_clear_tick(timer_base);
      ntick++;
    } // end if
  } // end while
}

/***********************************************************************
* function: main()
* purpose:  advanced flashing LED system using ad hoc driver
* note:
***********************************************************************/
int  main(){
  cmd_type sw_cmd={0,100};  // initial value: not pause, 100 ms interval

  flashsys_init_v1(BTN_BASE, USR_TIMER_BASE);
  while(1){
    sw_get_command_v1(BTN_BASE, SWITCH_BASE ,&sw_cmd);
    jtaguart_disp_msg_v1(JTAG_UART_BASE, sw_cmd);
    sseg_disp_msg_v1(SSEG_BASE, sw_cmd);
    led_flash_v1(LEDG_BASE, USR_TIMER_BASE, sw_cmd);
  }
}

/*
------------------------------------------------
Altera Nios2 Command Shell [GCC 4]

Version 10.0, Build 218
------------------------------------------------
bash-3.1$ nios2-elf-size K:/code/sopc_vhdl_src/ch10_11_12_nios_led2/exe/led2_ad
hoc.elf
   text    data     bss     dec     hex filename
  11500    5688     688   17876    45d4 K:/code/sopc_vhdl_src/ch10_11_12_nios_le
d2/exe/led2_adhoc.elf
bash-3.1$ nios2-elf-size K:/code/sopc_vhdl_src/ch10_11_12_nios_led2/exe/led2_ha
l.elf
   text    data     bss     dec     hex filename
  49412    6752     752   56916    de54 K:/code/sopc_vhdl_src/ch10_11_12_nios_le
d2/exe/led2_hal.elf
bash-3.1$
*/

