/***********************************************************************
*
* Module:  Advanced flashing-LED system using ISR with "context" argument
* File:    chu_main_led2_isr_v1.c
* Purpose: Task routines and main program
*
**********************************************************************/
/* include section */
/* General C library */
#include <stdio.h>
/* Altera-specific library */
#include "alt_types.h"
#include <sys/alt_irq.h>
#include "system.h"
/* Module-specific library */
#include "chu_avalon_gpio.h"
#include "chu_timer_drv.h"
/***********************************************************************
* data type definitions
***********************************************************************/
typedef struct flash_cmd{
  int pause;
  int prd;
} cmd_type;

typedef struct ctxt1{
  cmd_type *cmd_ptr;
  alt_u32 timer_base;
  alt_u32 led_base;
} ctxt1_type;

/***********************************************************************
* function: flash_led_isr()
* purpose:  isr for flash led
* argument:
*   context: pointer to context
*   id:
* return:
* note:
*   - cmd passed within context
***********************************************************************/
static void flash_led_isr(void* context, alt_u32 id)
{
  ctxt1_type *ctxt;
  cmd_type *cmd;
  static int ntick = 0;
  static unsigned char led_pattern = 0x01;

  /* type casting */
  ctxt = (ctxt1_type *) context;
  cmd = ctxt->cmd_ptr;
  /* clear "to" flag; also enable future interrupt */
  timer_clear_tick(ctxt->timer_base);
  if (cmd->pause)
    return;
  if (ntick < cmd->prd)
    ntick++;
  else {
    ntick = 0;
    led_pattern ^= 0x03;       // invert 2 LSBs
    pio_write(ctxt->led_base, led_pattern);
  }
}

/***********************************************************************
* function: flash_led_init_v1()
* purpose:  system initialization
* argument:
*   btn_base: base address of pushbutton PIO
*   timer_base: base address of timer
* return:
* note:
***********************************************************************/
void flash_led_init_v1(alt_u32 btn_base, alt_u32 timer_base)
{
  btn_clear(btn_base);              // clear button edge-capture reg
  timer_wr_prd(timer_base, 1000*50);  // for 1 ms tick
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
* function: main()
* purpose:  advanced flashing LED system using ISR with "context" argument
* note:
***********************************************************************/
int main(){
  cmd_type sw_cmd={0,100};  // not pause; 100 ms interval
  ctxt1_type ctxt1;

  flash_led_init_v1(BTN_BASE, USR_TIMER_BASE);
  ctxt1.led_base = LEDG_BASE;
  ctxt1.timer_base = USR_TIMER_BASE;
  ctxt1.cmd_ptr = &sw_cmd;
  alt_irq_register(USR_TIMER_IRQ, (void *) &ctxt1, flash_led_isr);
  while(1){
    sw_get_command_v1(BTN_BASE, SWITCH_BASE ,&sw_cmd);
    jtag_uart_disp_msg_v2(sw_cmd);
    sseg_disp_msg_v1(SSEG_BASE, sw_cmd);
  }
}

