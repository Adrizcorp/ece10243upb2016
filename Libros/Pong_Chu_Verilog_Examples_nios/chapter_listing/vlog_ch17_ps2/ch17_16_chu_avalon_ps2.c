/***********************************************************************
*
* Module:  PS2, keyboard, and mouse driver function prototypes
* File:    chu_avalon_ps2.c
* Purpose: Routines to access PS2 port and get keyboard scan codes and
*          mouse activities
*
***********************************************************************
/* file inclusion */
#include <io.h>
#include <unistd.h>            // to use usleep
#include "chu_avalon_ps2.h"



/***********************************************************************
* PS2 functions
************************************************************************
*
* Purpose: utility routines to read PS2 packets and send command
*
* Note:
*   - a fifo is used in receiver but not in transmitter
*   - reading (1st item of) fifo and removing the first item are
*     separated into two operations for flexibility
*
***********************************************************************/

/***********************************************************************
* function: ps2_tx_is_idle()
* purpose:  check whether the ps2 transmitter is idle
* argument:
*   ps2_base: base address of ps2 controller
* return: 1 if idle; 0 otherwise
* note:
***********************************************************************/
int ps2_tx_is_idle(alt_u32 ps2_base)
{
  alt_u32 ctrl_reg;
  int idle_bit;

  ctrl_reg = IORD(ps2_base, CHU_PS2_CONTROL_REG);
  idle_bit = (ctrl_reg & 0x00000002) >> 1;
  return idle_bit;
}

/***********************************************************************
* function: ps2_wr_cmd()
* purpose:  send an 8-bit command to ps2
* argument:
*   ps2_base: base address of ps2 controller
*   cmd: 8-bit command
* return:
* note:
*   - the code does not check whether ps2 is busy;
*     the calling function should not issue the command at a rapid rate
***********************************************************************/
void ps2_wr_cmd(alt_u32 ps2_base, alt_u8 cmd)
{
  IOWR(ps2_base, CHU_PS2_WR_DATA_REG, (alt_u32) cmd);
}

/***********************************************************************
* function: ps2_is_empty()
* purpose:  check whether the ps2 receiver fifo is empty
* argument:
*   ps2_base: base address of ps2 controller
* return: 1 if empty; 0 otherwise
* note:
***********************************************************************/
int ps2_is_empty(alt_u32 ps2_base)
{
  alt_u32 ctrl_reg;
  int empty_bit;

  ctrl_reg = IORD(ps2_base, CHU_PS2_CONTROL_REG);
  empty_bit = ctrl_reg & 0x00000001;
  return empty_bit;
}

/***********************************************************************
* function: ps2_read_fifo()
* purpose:  retrieve the data from the head of receiver fifo
* argument:
*   ps2_base: base address of ps2 controller
* return: data from the head of fifo
* note:
*   - the data remain in fifo after read
*   - invalid data returned if fifo is empty
***********************************************************************/
alt_u8 ps2_read_fifo(alt_u32 ps2_base)
{
  alt_u32 data_reg;
  alt_u8 packet;

  data_reg = IORD(ps2_base, CHU_PS2_DATA_REG);
  packet = (alt_u8) (data_reg & 0x000000ff);
  return packet;
}

/***********************************************************************
* function: ps2_rm_pkt()
* purpose:  remove data from the head of receiver fifo
* argument:
*   ps2_base: base address of ps2 controller
* return:
* note:
***********************************************************************/
void ps2_rm_pkt(alt_u32 ps2_base)
{
  IOWR(ps2_base, CHU_PS2_DATA_REG, 0x00000000); // write a dummy data
}

/***********************************************************************
* function: ps2_get_pkt()
* purpose:  check ps2 fifo and, if not empty, read data
* argument:
*   ps2_base: base address of ps2 controller
*   byte: pointer to the retrieved data
* return:
*   1 if data available; 0 otherwise
*   byte updated if data available
* note:
***********************************************************************/
int ps2_get_pkt(alt_u32 ps2_base, alt_u8 *byte)
{
  if (!ps2_is_empty(ps2_base)) {
    *byte = ps2_read_fifo(ps2_base);
    return 1;   // got data
  }
  return 0;     // no data
}

/***********************************************************************
* function: ps2_flush_fifo()
* purpose:  flush all packets from fifo
* argument:
*   ps2_base: base address of ps2 controller
* return:
* note:
***********************************************************************/
void ps2_flush_fifo(alt_u32 ps2_base)
{
  while (!ps2_is_empty(ps2_base)) {
    ps2_rm_pkt(ps2_base);
  }
}

/***********************************************************************
* function: ps2_reset_device()
* purpose:  reset and identify the type of ps2 device (mouse or keyboard)
* argument:
*   ps2_base: base address of ps2 controller
* return:
*    0: reset fails or unknown device; 1: keyboard; 2: mouse
* note:
*  - procedure:
*    1. flush ps2 receiver fifo
*    2. host sends reset command 0xff
*    3. ps2 device acknowledges (0xfa) and performs self-test
*    4. ps2 device responds 0xaa if test passes
*    5. mouse sends an extra id 0x00
***********************************************************************/
int ps2_reset_device(alt_u32 ps2_base)
{
  alt_u8 packet;

  ps2_flush_fifo(ps2_base);
  /* send reset 0xff  */
  ps2_wr_cmd(ps2_base, 0xff);
  usleep(1000000);     // wait for 200 ms
  /* check 0xfa 0xaa */
  if (ps2_get_pkt(ps2_base, &packet)==0 || packet!=0xfa)
    return (0);        // no response or wrong response
  ps2_rm_pkt(ps2_base);
  if (ps2_get_pkt(ps2_base, &packet)==0 || packet!=0xaa)
    return (0);        // no response or wrong response
  ps2_rm_pkt(ps2_base);
  /* check whether 0x00 is received */
  if (ps2_get_pkt(ps2_base, &packet)==0)
    return (1);        // fifo has no more packet, device is keyboard
  ps2_rm_pkt(ps2_base);
  if (packet==0x00)
    return (2);        // mouse id
  else
    return (0);        // unknown device id
}

/***********************************************************************
 * Keyboard functions
 ***********************************************************************
 *
 * Purpose: utility routines to process keyboard scan codes
 * Note:
 *
 ***********************************************************************/

/***********************************************************************
* function: kb_get_ch()
* purpose:  get a character or special key code from keyboard
* argument:
*   ps2_base: base address of ps2 controller
*   ch: pointer to the scanned charater
* return:
*   - 1 if there is a valid char; 0 otherwise
*   - ch updated with character or special key code
* note:
*   - cannot use extended scan codes
***********************************************************************/
int kb_get_ch (alt_u32 ps2_base, char *ch)
{
  // special  characters
  #define TAB     0x09   // tab
  #define BKSP    0x08   // backspace
  #define ENTER   0x0d   // enter (new line)
  #define ESC     0x1b   // escape
  #define BKSL    0x5c   // back slash
  #define SFT_L   0x12   // left shift
  #define SFT_R   0x59   // right shift

  #define CAPS    0x80
  #define NUM     0x81
  #define CTR_L   0x82
  #define F1      0xf0
  #define F2      0xf1
  #define F3      0xf2
  #define F4      0xf3
  #define F5      0xf4
  #define F6      0xf5
  #define F7      0xf6
  #define F8      0xf7
  #define F9      0xf8
  #define F10     0xf9
  #define F11     0xfa
  #define F12     0xfb

  // keyboard scan code to ascii (lowercase)
  static const char SCAN2ASCII_LO_TABLE[128]={
    0,    F9,    0,     F5,  F3,    F1,   F2,   F12,  //00
    0,    F10,   F8,    F6,  F4,    TAB,  '`',  0,    //08
    0,    0,     SFT_L, 0,   CTR_L, 'q',  '1',  0,    //10
    0,    0,     'z',   's', 'a',   'w',  '2',  0,    //18
    0,    'c',   'x',   'd', 'e',   '4',  '3',  0,    //20
    0,    ' ',   'v',   'f', 't',   'r',  '5',  0,    //28
    0,    'n',   'b',   'h', 'g',   'y',  '6',  0,    //30
    0,    0,     'm',   'j', 'u',   '7',  '8',  0,    //38
    0,    ',',   'k',   'i', 'o',   '0',  '9',  0,    //40
    0,    '.',   '/',   'l', ';',   'p',  '-',  0,    //48
    0,    0,     '\'',   0,  '[',   '=',  0,    0,    //50
    CAPS, SFT_R, ENTER, ']', 0,     BKSL, 0,    0,    //58
    0,    0,     0,     0,   0,     0,    BKSP, 0,    //60
    0,    '1',   0,     '4', '7',   0,    0,    0,    //68
    0,    '.',   '2',   '5', '6',   '8',  ESC,  NUM,  //70
    F11,  '+',   '3',   '-', '*',   '9',  0,    0     //78
  };
  // keyboard scan code to ascii (uppercase)
  static const char SCAN2ASCII_UP_TABLE[128] = {
    0,    F9,    0,     F5,  F3,    F1,   F2,   F12,  //00
    0,    F10,   F8,    F6,  F4,    TAB,  '~',  0,    //08
    0,    0,     SFT_L, 0,   CTR_L, 'Q',  '!',  0,    //10
    0,    0,     'Z',   'S', 'A',   'W',  '@',  0,    //18
    0,    'C',   'X',   'D', 'E',   '$',  '#',  0,    //20
    0,    ' ',   'V',   'F', 'T',   'R',  '%',  0,    //28
    0,    'N',   'B',   'H', 'G',   'Y',  '^',  0,    //30
    0,    0,     'M',   'J', 'U',   '&',  '*',  0,    //38
    0,    '<',   'K',   'I', 'O',   ')',  '(',  0,    //40
    0,    '>',   '?',   'L', ':',   'P',  '_',  0,    //48
    0,    0,     '\"',  0,   '{',   '+',  0,    0,    //50
    CAPS, SFT_R, ENTER, '}', 0,     '|',  0,    0,    //58
    0,    0,     0,     0,   0,     0,    BKSP, 0,    //60
    0,    '1',   0,     '4', '7',   0,    0,    0,    //68
    0,    '.',   '2',   '5', '6',   '8',  ESC,  NUM,  //70
    F11,  '+',   '3',   '-', '*',   '9',  0,    0     //78
  };

  static int sft_on = 0;
  alt_u8 scode;

  while (1){
    if (!ps2_get_pkt(ps2_base, &scode))         // no packet
      return(0);
    ps2_rm_pkt(ps2_base);
    switch (scode){
      case 0xf0:   // break code
        while (!ps2_get_pkt(ps2_base, &scode)); // get next
        ps2_rm_pkt(ps2_base);
      if (scode==SFT_L || scode==SFT_R)
        sft_on = 0;
        break;
     case SFT_L:                                // shift key make code
     case SFT_R:
     sft_on = 1;
       break;
     default:                                   // normal make code
       if (sft_on)
         *ch = SCAN2ASCII_UP_TABLE[scode];
       else
         *ch = SCAN2ASCII_LO_TABLE[scode];
       return(1);
    }  // end switch
  }  // end while
}

/***********************************************************************
* function: kb_get_line()
* purpose:  get a line from keyboard
*   ps2_base: base address of ps2 controller
*   s: pointer to the returned string
*   lim: max number in the string
* return: number of chars in the string
* note:
*   - procedure: read string until \n or max number reached
***********************************************************************/
int kb_get_line(alt_u32 ps2_base, char *s, int lim)
{
  char ch;
  int i;

  i=0;
  while (1){
    while(!kb_get_ch(ps2_base, &ch));
    if ((ch=='\n')|(i==(lim - 1)))
      break;
    else
      s[i++] = ch;
  } // end while
  s[i] = '\0';
  return i;
}

/***********************************************************************
 * Mouse functions
 ***********************************************************************
*
* Purpose: utility routines to process mouse command
*
* Note:
*    - no timeout for error checking
*
***********************************************************************/

/***********************************************************************
* function: mouse_init()
* purpose:  initialize mouse in stream mode
* argument:
*   ps2_base: base address of ps2 controller
* return:
*   1 if successful; 0 otherwise
* note:
*  - sequence:
*    1. reset mouse
*    3. host sends entering stream mode command 0xf4
*    4. mouse acknowledge with 0xfa
***********************************************************************/
int mouse_init(alt_u32 ps2_base)
{
  alt_u8 packet;

  if (ps2_reset_device(ps2_base)!=2)
    return (0);
  /* send stream mode command 0xf4  */
  ps2_wr_cmd(ps2_base, 0xf4);
  usleep(1000000);       // wait
  /* check 0xfa (acknowledge) */
  if (ps2_get_pkt(ps2_base, &packet)==0 || packet!=0xfa)
    return (0);          // no response or wrong response
  /* everything is ok */
  ps2_rm_pkt(ps2_base);
  return(1);
}

/***********************************************************************
* function: mouse_get_activity()
* purpose:  retrieve 3 packets and decode mouse movement info
* argument:
*   ps2_base: base address of ps2 controller
*   mv: pointer to the mouse movement data
* return:
*   * 1 if there is mouse activity; 0 otherwise
*   * mv updated if there is mouse activity
* note:
*   - ignore middle button
*   - ignore x, y overflow
*   - manually performing 9-bit signed to 32-bit integer
***********************************************************************/
int mouse_get_activity(alt_u32 ps2_base, mouse_mv_type *mv)
{
  alt_u8 b1, b2, b3;

  alt_u32 tmp;

  /* check and retrieve 1st byte */
  if (!ps2_get_pkt(ps2_base, &b1))
    return (0);                         // no data in rx fifo buffer
  ps2_rm_pkt(ps2_base);                 // remove 1st byte
  /* wait and retrieve 2nd byte */
  while (!ps2_get_pkt(ps2_base, &b2));  // get 2nd byte
  ps2_rm_pkt(ps2_base);
  /* wait and retrieve 3rd byte */
  while (!ps2_get_pkt(ps2_base, &b3));  // get 3rd byte
  ps2_rm_pkt(ps2_base);
  /* extract button info */
  mv->lbtn = (int) (b1 & 0x01);         // extract bit 0
  mv->rbtn = (int) (b1 & 0x02)>>1;      // extract bit 1
  /* extract x movement; manually convert 9-bit 2's comp to int */
  tmp = (alt_u32) b2;
  if (b1 & 0x10)                // check MSB (sign bit) of x movement
    tmp = tmp | 0xffffff00;     // manual sign-extension if negative
  mv->xmov = (int) tmp;         // data conversion
  /* extract y movement; manually convert 9-bit 2's comp to int */
  tmp = (alt_u32) b3;
  if (b1 & 0x20)                // check MSB (sign bit) of y movement
    tmp = tmp | 0xffffff00;     // manual sign-extension if negative
  mv->ymov = (int) tmp;         // data conversion
  /* success */
  return(1);
}
