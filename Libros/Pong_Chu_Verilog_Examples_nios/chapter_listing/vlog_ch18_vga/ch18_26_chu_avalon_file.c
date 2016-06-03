/***********************************************************************
*
* Module:  File retrieval function prototypes
* File:    chu_avalon_file.c
* Purpose: Simple file access routines
*          Note: must use debug mode to use host-based file system
*
***********************************************************************/
/* file inclusion */
#include <stdio.h>
#include "chu_avalon_file.h"


/***********************************************************************
* function: fskip()
* purpose:  skip a specific number of bytes in a file
* argument:
*   fp: file pointer
*   nbyte: # bytes to skip
* return:
* note:
***********************************************************************/
void fskip(FILE *fp, int nbyte)
{
  int i;
  for (i=0; i<nbyte; i++)
    fgetc(fp);
}

/***********************************************************************
* function: fget8()
* purpose:  get 8 bits (one byte) from a file
* argument:
*   fp: file pointer
* return: a byte in alt_u8 format
* note:
***********************************************************************/
alt_u8 fget8(FILE *fp)
{
  return( (alt_u8)fgetc(fp));
}

/***********************************************************************
* function: fget16()
* purpose:  get 16 bits (half word) from a file
* argument:
*   fp: file pointer
* return: a half word in alt_u16 format
* note: "little endian" byte ordering
***********************************************************************/
alt_u16 fget16(FILE *fp)
{
  alt_u16 b0, b1, r;

  b0 = (alt_u16) fgetc(fp);
  b1=  (alt_u16) fgetc(fp);
  r = (b1 << 8) + b0;
  return(r);
}

/***********************************************************************
* function: fget32()
* purpose:  get 32 bits (a word) from a file
* argument:
*   fp: file pointer
* return: a word in alt_u32 data type
* note: "little endian" byte ordering
***********************************************************************/
alt_u32 fget32(FILE *fp)
{
  alt_u32 b0, b1, b2, b3, r;

  b0 = (alt_u32) fgetc(fp);
  b1=  (alt_u32) fgetc(fp);
  b2=  (alt_u32) fgetc(fp);
  b3=  (alt_u32) fgetc(fp);
  r = (b3<<24) + (b2<<16) + (b1<<8) + b0;
  return(r);
}



