/***********************************************************************
*
* Module:  ddfs header
* File:    chu_avalon_ddfs.h
* Purpose: Routines to configure ddfs
*
************************************************************************
*  Address map
************************************************************************
* Write (data from cpu):
*   0x000: bits 25-0: 26-bit freq (carrier) control word
*   0x001: bits 25-0: 26-bit freq (offset) control word
*   0x002: bits 25-0: 26-bit phase offset
*   0x003: bits 15-0: 16-bit envelope
*   0x1xx: bits 15-0: 16-bit phase-to-amplitude LUT data
*
***********************************************************************/
/* file inclusion */
#include <alt_types.h>

/***********************************************************************
* constant definitions
***********************************************************************/
#define CHU_DDFS_FCCW_REG     0
#define CHU_DDFS_FOCW_REG     1
#define CHU_DDFS_PHA_REG      2
#define CHU_DDFS_ENV_REG      3

#define DDFS_PW     26        // width (#bits) of ddfs phase accumulator
#define DDFS_F_SYS  50000000  // ddfs system reference frequency 50 MHz

/***********************************************************************
* Function prototypes
***********************************************************************/
void ddfs_wr_carrier_freq(alt_u32 ddfs_base, alt_u32 freq);
void ddfs_wr_offset_freq(alt_u32 ddfs_base, alt_u32 freq);
void ddfs_wr_pha(alt_u32 ddfs_base, int offset);
void ddfs_wr_env(alt_u32 ddfs_base, alt_16 env);
void ddfs_init(alt_u32 audio_base, alt_u32 ddfs_base);
