/***********************************************************************
*
* Module:  VGA video driver function prototypes
* File:    chu_avalon_vga.c
* Purpose: Routines to access video SRAM and display bit-mapped graphics
*          and text
*
***********************************************************************
/* file inclusion */
#include <stdlib.h>                       // to use abs()
#include <io.h>
#include "chu_avalon_vga.h"
#include "chu_avalon_vga_font_table.h"

/***********************************************************************
* function: vga_calc_sram_addr()
* purpose:  calculate the video SRAM address offset for location (x, y)
* argument:
*   x: x-axis coordinate, 10 LSBs used
*   y: y-axis coordinate, 9 LSBs used
* return:
*   address
* note:
*   - for a Nios II configuration without hardware multiplier, use shift:
*     offset= 640*y + x = 512*y + 128*y + x = y<<9 + y<<7 +x
***********************************************************************/
alt_u32 vga_calc_sram_addr(int x, int y)
{
  alt_u32 addr;

  addr = (alt_u32) (DISP_GRF_X_MAX*y + x);
  return addr;
}

/***********************************************************************
* function: vga_rd_pix()
* purpose:  read a pixel from location (x,y)
* argument:
*   vga_base: base address of video SRAM
*   x: x-axis coordinate, 10 LSBs used
*   y: y-axis coordinate, 9 LSBs used
* return:
*   8-bit color at (x,y)
* note:
***********************************************************************/
alt_u8 vga_rd_pix(alt_u32 vga_base, int x, int y)
{
  alt_u32 offset;
  alt_u8 color;

  offset = vga_calc_sram_addr(x,y);           // form address offset
  color = (alt_u8) IORD(vga_base, offset);    // read video memory
  return color;
}

/***********************************************************************
* function: vga_rd_xy()
* purpose:  get current scan coordinate (x,y)
* argument:
*   vga_base: base address of video SRAM
*   x: pointer to current value of VGA sync horizontal counter
*   y: pointer to current value of VGA sync vertical counter
* return:
*   updated x, y
* note:
***********************************************************************/
void vga_rd_xy(alt_u32 vga_base, int *x, int *y)
{
  alt_u32 data;
  const alt_u32 XY_ADDR=0x00080000;

  data = IORD(vga_base, XY_ADDR);   // read video SRAM
  *x = 0x000003ff & data;           // 10 LSBs for horizontal counter
  *y = 0x000003ff & (data >> 10);   // next 10 LSBs for vertical counter
  return;
}

/***********************************************************************
 * function: vga_wr_pix()
 * purpose:  write a pixel to location (x,y)
 * argument:
 *   vga_base: base address of video SRAM
 *   x: x-axis coordinate, 10 LSBs used
 *   y: y-axis coordinate, 9 LSBs used
 *   color: 8-bit color
 * return:
 * note:
 ***********************************************************************/
void vga_wr_pix(alt_u32 vga_base, int x, int y, alt_u8 color)
{
  alt_u32 offset;

  offset = vga_calc_sram_addr(x,y);     // form address offset
  IOWR(vga_base, offset, color);        // write video SRAM
  return;
}

/***********************************************************************
 * function: vga_plot_line()
 * purpose:  draw a line from (x1,y1) to (x2,y2)
 * argument:
 *   vga_base: base address of video SRAM
 *   x1, y1: starting point
 *   x2, y2: end point
 *   color: 8-bit color
 * return:
 * note:
 *  - plot increments via x-axis for "horizontal" line
 *    and via y-axis for "vertical line" (steep line)
 *  - not optimized (need floating-point multiplication for each point)
 ***********************************************************************/
void vga_plot_line(alt_u32 vga_base, int x1, int y1, int x2, int y2,
                    alt_u8 color)
{
  int horiz, step, x, y;
  float slope;

  if ((y1==y2) && (x1==x2)){   // special case of x1==x2 and y1==y2
     vga_wr_pix(vga_base, x1, y1, color);
     return;
  }
  horiz = (abs(x2-x1)>abs(y2-y1)) ? 1 : 0;
  if (horiz){   // line is more horizontal and x2!=x1
    slope=(float)(y2-y1) / (float)(x2-x1);
    step = ((x2-x1)>1) ? 1 : -1;
    for(x=x1;x!=x2;x=x+step){
      y = slope*(x-x1) + y1;
      vga_wr_pix(vga_base, x, y, color);
    } // end for
  } else {       //  line is more vertical
    slope=(float)(x2-x1)/ (float)(y2-y1);
    step = ((y2-y1)>1) ? 1 : -1;
    for(y=y1;y!=y2;y=y+step){
      x = slope*(y-y1) + x1;
      vga_wr_pix(vga_base, x, y, color);
    } // end for
  }
  return;
}

/***********************************************************************
* function: vga_clr_screen()
* purpose:  clear the screen to a background color
* argument:
*   vga_base: base address of video SRAM
*   color: background color
* return:
* note:
***********************************************************************/
void vga_clr_screen(alt_u32 vga_base, alt_u8 color)
{
  int x, y;

  for(x=0; x<DISP_GRF_X_MAX; x++)
    for(y=0; y<DISP_GRF_Y_MAX; y++)
      vga_wr_pix(vga_base, x, y, color);
}

/***********************************************************************
* function: vga_wr_bitmap()
* purpose:  write a bitmap to video SRAM starting at (x,y)
* argument:
*   vga_base: base address of video SRAM
*   x: x-axis coordinate, 10 LSBs used
*   y: y-axis coordinate, 9 LSBs used
*   bmp: pointer to the bitmap structure
*   tran: whether to draw transparent background
*         0: draw black pixels in the background bitmap
*         1: not draw black pixels in the background bitmap
* return:
* note:
***********************************************************************/
void vga_wr_bitmap(alt_u32 vga_base, int x, int y, bmp_type *bmp,
                   int tran)
{
  int i,j;
  alt_u8 color;

  for(j=0;j<bmp->height;j++){
    for(i=0;i<bmp->width;i++){
      color = bmp->pdata[(j*bmp->width) + i];
      if (tran==0 || color!=0)
        vga_wr_pix(vga_base, i+x, j+y, color);
    } // end for loop i
  } // end for loop j
}

/***********************************************************************
* function: vga_rd_bitmap()
* purpose:  read a bitmap from video SRAM starting at (x,y)
* argument:
*   vga_base: base address of video SRAM
*   x: x-axis coordinate, 10 LSBs used
*   y: y-axis coordinate, 9 LSBs used
*   bmp: pointer to the returned bitmap structure
* return: updated bmp structure
* note: the calling function must allocate memory for the retrieved
*       "bmp" bitmap structure
***********************************************************************/
void vga_rd_bitmap(alt_u32 vga_base, int x, int y, bmp_type *bmp)
{
  int i,j;
  alt_u8 color;

  for(j=0;j<bmp->height;j++){
    for(i=0;i<bmp->width;i++){
      color = vga_rd_pix(vga_base, i+x, j+y);
      bmp->pdata[(j*bmp->width) + i] = color;
    } // end for loop i
  } // end for loop j
}

/***********************************************************************
* function: vga_move_bitmap()
* purpose:  move an overlay bitmap from (xold,yold) to (xnew,ynew)
* argument:
*   vga_base: base address of video SRAM
*   xold: current x-axis coordinate, 10 LSBs used
*   yold: current y-axis coordinate, 9 LSBs used
*   below: pointer to the buffer that stores the pixels below bmp
*   xnew: new x-axis coordinate, 10 LSBs used
*   ynew: new y-axis coordinate, 9 LSBs used
*   bmp: pointer to bitmap
* return:
*   underlying pixels at (xnew,ynew) are stored into bellow buffer
* note:
*   - underlying pixels at (xold,yold) were stored in below buffer
*     before the function is called
*   - the calling functioning must allocate memory for below buffer
***********************************************************************/
void vga_move_bitmap(alt_u32 vga_base,
                     int xold, int yold, bmp_type *below,
                     int xnew, int ynew, bmp_type *bmp)
{
  /* restore the hidden pixels at (xold, yold) */
  vga_wr_bitmap(vga_base, xold, yold, below, 0);
  /* read the hidden pixels at (xnew, ynew) */
  vga_rd_bitmap(vga_base, xnew, ynew, below);
  /* write the top bitmap at (xnew, ynew) */
  vga_wr_bitmap(vga_base, xnew, ynew, bmp, 1);
}

/***********************************************************************
* function: vga_wr_bit_ch()
* purpose:  write a char to video SRAM at (x,y); use 0x7f to erase
* argument:
*   vga_base: base address of video SRAM
*   x: x-axis coordinate, 9 LSBs used
*   y: y-axis coordinate, 8 LSBs used
*   ch: ascii character (only 7 LSBs used)
*   color: character color
*   zoom: zoom factor (usually 1 to 3)
* return:
* note:
*  - the font is 8 pixels wide and 16 pixels tall
*  - zoom only magnifies 1-by-1 pixel to 2-by-2 or 3-by-3 pixels and
*    char shows jagged edge
*  - 0x7f fills tile with solid color and
*    can be used to erase a char by using background color
***********************************************************************/
void vga_wr_bit_ch(alt_u32 vga_base, int x, int y, char ch, int color,
                   int zoom)
{
  int i,j, ch_line_addr, bit;
  alt_u8 row;

  for(j=0; j<16*zoom; j++){
    /* get a row from font table */
    ch_line_addr = 16*ch + j/zoom;   // char base address + offset
    row = FONT[ch_line_addr];
    /* process bit */
    for(i=0;i<8*zoom;i++){
      bit = row & (0x80 >> (i/zoom));
      if (bit!=0)
        vga_wr_pix(vga_base, x+i, y+j, color);
    } // end for loop i
  } // end for loop j
}


/***********************************************************************
* function: vga_wr_bit_string()
* purpose:  write a string to video SRAM at (x,y);
* argument:
*   vga_base: base address of video SRAM
*   x: x-axis coordinate, 9 LSBs used
*   y: y-axis coordinate, 8 LSBs used
*   s: pointer to the string
*   color: character color
*   zoom: zoom factor (usually 1 to 3)
* return:
* note:
************************************************************************/
void vga_wr_bit_str(alt_u32 vga_base, int x, int y, char *s,
                    int color, int zoom)
{
  int cx, cy;         // current x, y

  cx = x;
  cy = y;
  while (*s) {
    if (*s=='\n') {   // new line
      cx = x;
      cy = cy + 16*zoom;
      s++;
    }
    else {
      vga_wr_bit_ch(vga_base, cx, cy, *s, color, zoom);
      s++;
      cx = cx + 8*zoom;
    }  // end else
  }  // end while
}
