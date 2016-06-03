/***********************************************************************
*
* Module:  File retrieval header
* File:    chu_avalon_file.h
* Purpose: Simple file access routines
*
***********************************************************************/
/* file inclusion */
#include <alt_types.h>
#include <stdlib.h>
#include <io.h>

/***********************************************************************
* Function prototypes
***********************************************************************/
/* basic file access routines */
void fskip(FILE *fp, int nbyte);
alt_u8 fget8(FILE *fp);
alt_u16 fget16(FILE *fp);
alt_u32 fget32(FILE *fp);


