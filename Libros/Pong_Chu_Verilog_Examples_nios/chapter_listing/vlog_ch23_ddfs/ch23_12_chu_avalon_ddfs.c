/***********************************************************************
*
* Module:  DDFS driver function prototypes
* File:    chu_avalon_ddfs.c
* Purpose: Routines to configure ddfs
*
************************************************************************
*  Register map
************************************************************************
* Write (data from cpu):
*   offset 0x000
*     * bits 25-0: 26-bit freq (carrier) control word
*   offset 0x001
*     * bits 25-0: 26-bit freq (offset) control word
*   offset 0x002
*     * bits 25-0: 26-bit phase offset
*   offset 0x003
*     * bits 15-0: 16-bit envelope
*   offset 0x100 to 0xff
*     * bits 15-0: 16-bit phase-to-amplitude LUT data
*
***********************************************************************/
/* file inclusion */
#include <io.h>
#include "chu_avalon_ddfs.h"
#include "chu_avalon_audio.h"

#define power2n(n) (1<<(n))   //2^n is same as shifting 1 to left n bits

/***********************************************************************
* function: ddfs_wr_carrier_freq()
* purpose:  set freq (carrier) control word of dffs
*           fccw = freq*2^DDFS_PW/DDFS_F_SYS
* argument:
*   ddfs_base: base address of ddfs
*   freq: carrier frequency
* return:
* note:
************************************************************************/
void ddfs_wr_carrier_freq(alt_u32 ddfs_base, alt_u32 freq)
{
  float tmp;
  alt_u32 fccw;

  tmp = ((float) power2n(DDFS_PW)) / ((float) DDFS_F_SYS);
  fccw = (alt_u32) (freq * tmp);
  IOWR(ddfs_base, CHU_DDFS_FCCW_REG, fccw);
}

/***********************************************************************
* function: ddfs_wr_offset_freq()
* purpose:  set freq (offset) control word of dffs
*           focw = freq*2^DDFS_PW/DDFS_F_SYS
* argument:
*   ddfs_base: base address of ddfs
*   freq: offset frequency
* return:
* note:
************************************************************************/
void ddfs_wr_offset_freq(alt_u32 ddfs_base, alt_u32 freq)
{
  float tmp;
  alt_u32 focw;

  tmp = ((float) power2n(DDFS_PW)) / ((float) DDFS_F_SYS);
  focw = (alt_u32) (freq * tmp);
  IOWR(ddfs_base, CHU_DDFS_FOCW_REG, focw);
}

/***********************************************************************
* function: ddfs_wr_pha()
* purpose:  set phase offset
*       offset = (deg/360) *2^DDFS_PW
* argument:
*   ddfs_base: base address of ddfs
*   offset: phase offset in degrees
* return:
* note:
************************************************************************/
void ddfs_wr_pha(alt_u32 ddfs_base, int offset)
{
  alt_u32 pcw;

  pcw =  offset*DDFS_F_SYS/360 ;
  IOWR(ddfs_base, CHU_DDFS_PHA_REG, pcw);
}

/***********************************************************************
* function: ddfs_wr_env()
* purpose:  set envelope
* argument:
*   ddfs_base: base address of ddfs
*   env: envelope
* return:
* note:
************************************************************************/
void ddfs_wr_env(alt_u32 ddfs_base, alt_16 env)
{
  IOWR(ddfs_base, CHU_DDFS_ENV_REG, env);
}

/***********************************************************************
* function: ddfs_init()
* purpose:  initialize ddfs
* argument:
*   ddfs_base: ase address of ddfs
* note: use audio_init() to initialize codec and then
*       route dac data to external bus
***********************************************************************/
void ddfs_init(alt_u32 audio_base, alt_u32 ddfs_base)
{
  audio_init(audio_base);
  audio_wr_src_sel(audio_base, 1, 0);   // dac to external bus
  ddfs_wr_carrier_freq(ddfs_base, 262); // mid C frequency
  ddfs_wr_offset_freq(ddfs_base, 0);
  ddfs_wr_pha(ddfs_base, 0);
  ddfs_wr_env(ddfs_base, 0x7fff);       // close to 1.0
}


/***********************************************************************
* function: ddfs_wr_p2a_ram()
* purpose:  write phase-to-amplitude LUT RAM
* argument:
*   ddfs_base: base address of ddfs
*
* return:
* note:
***********************************************************************/
/*void ddfs_wr_p2a_ram(alt_u32 audio_base)
{
}
*/

