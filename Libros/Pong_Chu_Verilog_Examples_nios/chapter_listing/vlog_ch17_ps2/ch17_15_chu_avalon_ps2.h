/***********************************************************************
*
* Module:  PS2, keyboard, and mouse driver header
* File:    chu_avalon_ps2.h
* Purpose: Routines to access PS2 port and get keyboard scan codes and
*          mouse activities
*
************************************************************************
* Register map
************************************************************************
* Read (data to cpu):
*   offset 0
*     * bit 7-0: 8-bit ps2 packet
*   offset 1
*     * bit 0: ps2 receiving fifo empty
*     * bit 1: ps2 transmitter idle
* Write (data from cpu):
*   offset 0:  dummy data, used to generate an enable pulse
*   offset 2:
*     * bit 7-0: 8-bit ps2 command data
*
***********************************************************************/
/* file inclusion */
#include <alt_types.h>

/***********************************************************************
* constant definitions
***********************************************************************/
#define CHU_PS2_DATA_REG      0
#define CHU_PS2_CONTROL_REG   1
#define CHU_PS2_WR_DATA_REG   2

/***********************************************************************
* Data type definitions
***********************************************************************/
/* data type for mouse activities */
typedef struct mouse_move
{
  int lbtn;    // left button
  int rbtn;    // right button
  int xmov;    // x-axis movement
  int ymov;    // x-axis movement
} mouse_mv_type;

/***********************************************************************
* Function prototypes
***********************************************************************/
/* PS2 functions */
int ps2_tx_is_idle(alt_u32 ps2_base);
void ps2_wr_cmd(alt_u32 ps2_base, alt_u8 cmd);
int ps2_is_empty(alt_u32 ps2_base);
alt_u8 ps2_read_fifo(alt_u32 ps2_base);
void ps2_rm_pkt(alt_u32 ps2_base);
int ps2_get_pkt(alt_u32 ps2_base, alt_u8 *byte);
void ps2_flush_fifo(alt_u32 ps2_base);
int ps2_reset_device(alt_u32 ps2_base);

//* Keyboard functions */
int kb_get_ch (alt_u32 ps2_base, char *ch);
int kb_get_line(alt_u32 ps2_base, char *s, int lim);

/* Mouse functions */
int mouse_init(alt_u32 ps2_base);
int mouse_get_activity(alt_u32 ps2_base, mouse_mv_type *mv);

