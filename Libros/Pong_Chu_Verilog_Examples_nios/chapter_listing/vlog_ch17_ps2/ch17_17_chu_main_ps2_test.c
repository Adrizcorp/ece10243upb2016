/***********************************************************************
*
* Module:  PS2, keyboard, and mouse test
* File:    chu_main_ps2_test.c
* Purpose: Test PS2, keyboard and mouse driver routines
* IP core base addresses:
*    - SWITCH_BASE: slide switch
*    - BTN_BASE: pushbutton
*    - LED_BASE: discrete LEDs
*    - SSEG_BASE: 7-segment LED
*    - PS2_BASE: PS2 controller
*
***********************************************************************/
/* file inclusion */
#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "chu_avalon_gpio.h"
#include "chu_avalon_ps2.h"


/***********************************************************************
* function: mouse_led()
* purpose:  use mouse x-axis movement to control 8 leds
* argument:
*   led_base: base address of discrete LEDs
*   mv: pointer to mouse movement data
* return:
* note:
***********************************************************************/
void mouse_led(alt_u32 led_base, mouse_mv_type *mv){
  static int count=0;
  int pos;
  alt_u32 led_ptn;

  if(mv->lbtn)
    count = 0;
  else if (mv->rbtn)
    count = 255;
  else{
    count = count + mv->xmov;
    if (count>255)
      count = 255;
    if (count<0)
      count = 0;
  }
  pos = (count >> 5);             // get 3 MSBs
  led_ptn = (0x00000080) >> pos;  // 0b10000000
  pio_write(led_base, led_ptn);
}

/***********************************************************************
* function: main()
* purpose:  test PS2, keyboard, and mouse operations
* note:
*   - keyboard/mouse operation assumes that the fifo is empty initially;
*     perform "display ps2 stream" first to flush the fifo buffer
***********************************************************************/
int main(void){
  alt_u8 cmd, packet;
  int sw, btn, id;
  mouse_mv_type mv;
  char ch;
  alt_u8 ps2_msg[4]={0xff,0x0c,sseg_conv_hex(5),sseg_conv_hex(2)};

  sseg_disp_ptn(SSEG_BASE, ps2_msg);               // display " PS2"
  printf("PS2 test: \n");
  btn_clear(BTN_BASE);
  while (1){
    while (!btn_is_pressed(BTN_BASE)){ };          // wait for button
    btn=btn_read(BTN_BASE);                        // read button
    if (btn & 0x02){                               // key1 pressed
      sw=pio_read(SWITCH_BASE);                    // read switch
      printf("key/sw: %d/%d\n", btn, sw);
    }
    btn_clear(BTN_BASE);
    switch (sw){
      case 0:   // reset
        id=ps2_reset_device(PS2_BASE);
        printf("PS2 device type: %d (0/1/2: unknown/keyboard/mouse)\n", id);
        break;
      case 1:   // initialize mouse to stream mode
        id=mouse_init(PS2_BASE);
        printf("Mouse initialization status: %d (0/1: fail/succeed)\n", id);
        break;
      case 2:   // issue a ps2 command
        printf("Enter ps2 command in 2-digit hex format:\n");
        scanf("%x", &cmd);
        ps2_wr_cmd(PS2_BASE, cmd);
        printf("PS2 command 0x%02x issued.\n", cmd);
        usleep(500000);       // wait
        printf("PS2 response: ");
        while (ps2_get_pkt(PS2_BASE, &packet)){  // get all packets
          printf("0x%02x  ", packet);
          ps2_rm_pkt(PS2_BASE);
        }
        printf("\n");
        break;
      case 3:   // display ps2 stream
        printf("PS2 packet stream:\n");
        while (!btn_is_pressed(BTN_BASE)){
          if (ps2_get_pkt(PS2_BASE, &packet)){   // get one packet
            printf("0x%02x ", packet);
            ps2_rm_pkt(PS2_BASE);
          }
        }
        printf("\n");
        break;
      case 4:   // display decoded keyboard input stream
        printf("Keyboard char stream: \n");
        while (!btn_is_pressed(BTN_BASE)){
          if (kb_get_ch(PS2_BASE, &ch))
              printf("%c", ch);
        }
        printf("\n");
        break;
      case 5:   // display decoded mouse data stream
        printf("Mouse data stream: (left button, right button, "
               "x-axis move, y-axis move)\n");
        while (!btn_is_pressed(BTN_BASE)){
          if (mouse_get_activity(PS2_BASE, &mv)){
            printf("(%d,%d,%d,%d) ", mv.lbtn, mv.rbtn, mv.xmov, mv.ymov);
            mouse_led(LED_BASE, &mv);
          }
        }
        printf("\n");
        break;
    }  //end switch
  } // end while
}

