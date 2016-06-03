/***********************************************************************
*
* Module:  Fractal function prototypes and main
* File:    chu_main_frac_test.c
* Purpose: software- and hardware-accelerator-based fractal routines
* IP core base addresses:
*   - SSEG_BASE: 7-segment LED display
*   - VRAM_BASE: video SRAM
*   - PS2_BASE: PS2 controller
*   - SWITCH_BASE: slide switch
*   - F_ENGINE_BASE: fractal hardware accelerator engine
*
************************************************************************
*  Register map
************************************************************************
* Write (data from cpu):
*   offset 0
*     * bits 31-0: cx
*   offset 1
*     * bits 31-0: cy
*   offset 2
*     * bits 15-0: maximal iterations
*   offset 3
*     * dummy data to start operation
* Read (data to cpu):
*   offset 0
*     * bit 16: 1-bit ready signal
*     * bits 15 - 0: 16-bit iteration value
***********************************************************************/
/* file inclusion */
/* General C library */
#include <stdio.h>
#include <unistd.h>
/* Altera-specific library */
#include "system.h"
#include "chu_avalon_gpio.h"
#include "chu_avalon_vga.h"
#include "chu_avalon_ps2.h"


/* data type definition */
typedef alt_32 fixed428;          // define 32-bit Q4.28 fixed data type
typedef alt_64 fixed856;          // define 64-bit Q8.56 fixed data type

/* macro definition */
#define f2f(x) (x)*(1.0/(1<<28))  // convert Q4.28 to floating

/* address and field definition */
#define CX_REG           0
#define CY_REG           1
#define MAX_ITR_REG      2
#define FRAC_START_REG   3
#define ITR_DATA_REG     0
#define ITR_FIELD        0x0000ffff
#define FRAC_READY_BIT   0x00010000

/* constant definition */
#define WD      (0x30000000)   // width of initial fractal: +3 in Q4.28
#define FPIX    480            // # pixels in each axis in fractal

/* 12-row-by-20-column 8-bit-color mouse pointer bitmap array */
alt_u8 MOUSE_DATA[]=
  {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x92, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x92, 0x92, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x92, 0x92, 0x92, 0x6d, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x6d, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x6d, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x6d, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x92, 0x92, 0x6d, 0x6d, 0x6d, 0x6d, 0x6d, 0x6d,
  0x00, 0xff, 0x92, 0x92, 0x6d, 0x92, 0x92, 0x6d, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x92, 0x00, 0x6d, 0x92, 0x92, 0x6d, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x92, 0x00, 0x00, 0x6d, 0x92, 0x92, 0x6d, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x92, 0x92, 0x6d, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x92, 0x92, 0x6d, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x92, 0x92, 0x6d, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x92, 0x92, 0x6d, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x6d, 0x00, 0x00
  };
/* 2-row-by-20-column 8-bit-color mouse pointer bitmap data structure */
bmp_type MOUSE_BMP={
  12,          // width
  20,          // height
  MOUSE_DATA   // bitmap array
};

/***********************************************************************
* function: calc_frac_point_soft()
* purpose:  calculate one fractal point with Q4.28 fixed-point data type
* argument:
*   cx: cx value in Q4.28
*   cy: cy value in Q4.28
*   max_itr: max number of iterations
* return: # iteration when escape condition reached
* note: return max_itr if sequence not diverge
***********************************************************************/
int calc_frac_point_soft(fixed428 cx, fixed428 cy, alt_u16 max_itr)
{
  fixed428 x, y, xx, yy, xy2;
  fixed856 xx_raw, yy_raw, xy_raw;
  int itr;

  x = cx;
  y = cy;
  itr = 0;
  do {
    /* Q4.28 multiplications */
    xx_raw = (fixed856)(x) * (fixed856)(x);
    xx = (fixed428)(xx_raw >> 28);
    yy_raw = (fixed856)(y) * (fixed856)(y);
    yy = (fixed428)(yy_raw >> 28);
    xy_raw = (fixed856)(x) * (fixed856)(y);
    xy2 = (fixed428)(xy_raw >> 27);  // 2* is same as <<1
    /* iteration equation */
    x = xx - yy + cx;
    y = xy2 + cy;
    itr++;;
  } while (((xx+yy)<0x40000000) && (itr<max_itr));
  return(itr);
}

/***********************************************************************
* function: calc_frac_point_hard()
* purpose:  calculate one fractal point with hardware accelerator
* argument:
*   frac_base: base address of fractal engine
*   cx: cx value in Q4.28
*   cy: cy value in Q4.28
*   max_itr: max number of iterations
* return: # iteration when escape condition reached
* note: return max_itr if sequence not diverge
***********************************************************************/
int calc_frac_point_hard(alt_u32 frac_base, fixed428 cx, fixed428 cy,
                        alt_u16 max_itr)
{
  alt_u32 data;
  int itr;

  IOWR(frac_base, CX_REG, (alt_u32) cx);
  IOWR(frac_base, CY_REG, (alt_u32) cy);
  IOWR(frac_base, MAX_ITR_REG, (alt_u32) max_itr);
  IOWR(frac_base, FRAC_START_REG, 0); // write dummy to start operation
  while(1){
    data=IORD(frac_base, ITR_DATA_REG);
    if (data & FRAC_READY_BIT)        // check 17th bit for ready signal
      break;
  }
  itr = data & ITR_FIELD;             // get 16-bit result
  return(itr);
}

/***********************************************************************
* function: draw_fractal()
* purpose:  draw fractal graphic
* argument:
*   vga_base: base address of VGA video ram
*   frac_base: base address of fractal engine
*   engine: engine to do computation (0 for software; 1 for accelerator)
*   cx0: initial cx value in Q4.28 (left bottom point in cx-cy plane)
*   cy0: initial cy value in Q4.28 (left bottom point in cx-cy plane)
*   delta: value between two successive points in fractal in Q4.28
*   max_itr: max number of iterations
* return:
* note:
***********************************************************************/
void draw_fractal(alt_u32 vga_base, alt_u32 frac_base, int engine,
              fixed428 cx0, fixed428 cy0, fixed428 delta, int max_itr)
{
  int i, j;
  int itr;
  alt_u8 color;
  fixed428 cx, cy;

  cy = cy0;
  for(j=0; j<FPIX; j++){
    cx = cx0;
    for(i=0; i<FPIX; i++){
      /* calculate one point */
      if (engine==0)
        itr = calc_frac_point_soft(cx, cy, max_itr);
      else
       itr = calc_frac_point_hard(frac_base, cx, cy, max_itr);
      /* coloring scheme */
      if (itr==max_itr)
         color = 0x00;  // no escape; black
      else
         color = (alt_u8)((0xd0 & itr)>>6) + (alt_u8)(itr<<2) ;
      /* write a pixel on VGA */
      vga_wr_pix(vga_base, i, 479-j, color);
      cx = cx + delta;
    } // end for i
    cy = cy + delta;
  } // end for j
}

/***********************************************************************
* function: disp_msg()
* purpose:  display message on right panel of VGA
* argument:
*   vga_base: base address of VGA video ram
* return:
* note:
***********************************************************************/
void disp_msg(alt_u32 vga_base)
{
  char help_msg[]=
    "HELP:               \n"
    "-left-click mouse   \n"
    " to select menu     \n"
    " or set center      \n"
    "-use switch to set  \n"
    " desired value      \n";
  char para_msg[]=
    "PARAMETERS          \n"
    "center x:           \n"
    "center y:           \n"
    "delta   :           \n"
    "zoom    :           \n"
    "max iter:           \n"
    "engine  :           \n";
  char menu_msg[]=
    "MENU:               \n"
    "- load zoom level   \n"
    "- load max iter     \n"
    "- select engine     \n"
    "- restore initial   \n"
    "- start drawing     \n";

  vga_wr_bit_str(vga_base, 485, 0, menu_msg, 0xff, 1);
  vga_wr_bit_str(vga_base, 485, 16*10, para_msg, 0xff, 1);
  vga_wr_bit_str(vga_base, 485, 16*20, help_msg, 0xff, 1);
}

/***********************************************************************
* function: disp_param()
* purpose:  display parameter values on right panel of VGA
* argument:
*   vga_base: base address of VGA video ram
*   cx_c: center cx value in Q4.28 (center of cx-cy plane)
*   cy_c: center cy value in Q4.28 (center of cx-cy plane)
*   delta: value between two successive points in fractal in Q4.28
*   zoom: zoom factor
*   max_itr: max number of iterations
*   engine: engine used (0 for software; 1 for accelerator)
* return:
* note:
***********************************************************************/
void disp_param(alt_u32 vga_base, fixed428 cx_c, fixed428 cy_c,
                fixed428 delta, int zoom, int max_itr, int engine)
{
  char s[]="123456789";
  char erase[]= "\x7f\x7f\x7f\x7f\x7f\x7f\x7f\x7f\x7f";
  int x_offset = 485+8*10;
  int y0 = 11;
  int i;

  /* clear old field */
  for (i=0; i<6; i++)
    vga_wr_bit_str(vga_base, x_offset, 16*(y0+i), erase, 0x00, 1);
  /* draw new values */
  sprintf(s, "%+2.6f", f2f(cx_c));
  vga_wr_bit_str(vga_base, x_offset, 16*y0, s, 0xff, 1);
  sprintf(s, "%+2.6f", f2f(cy_c));
  vga_wr_bit_str(vga_base, x_offset, 16*(y0+1), s, 0xff, 1);
  sprintf(s, "%+2.6f", f2f(delta));
  vga_wr_bit_str(vga_base, x_offset, 16*(y0+2), s, 0xff, 1);
  sprintf(s, "2^%d", zoom);
  vga_wr_bit_str(vga_base, x_offset, 16*(y0+3), s, 0xff, 1);
  sprintf(s, "%d", max_itr);
  vga_wr_bit_str(vga_base, x_offset, 16*(y0+4), s, 0xff, 1);
  sprintf(s, "%d", engine);
  vga_wr_bit_str(vga_base, x_offset, 16*(y0+5), s, 0xff, 1);
}

/***********************************************************************
* function: vga_init_mouse_ptr()
* purpose:  initialize the mouse pointer by writing pointer bitmap
*           at (x,y) and saving the underlying pixels in below buffer
* argument:
*   vga_base: base address of VGA video ram
*   ps2_base: base address of PS2 device
*   x: x-axis coordinate, 10 LSBs used
*   y: y-axis coordinate, 9 LSBs used
*   mouse: pointer to mouse pointer bitmap
*   below: pointer to the buffer storing pixels below mouse pointer
* return:
*   underlying pixels at (x,y) are stored into bellow buffer
* note:
*   - the calling function must allocate memory for "below" buffer
***********************************************************************/
void vga_init_mouse_ptr(alt_u32 vga_base,  alt_u32 ps2_base,
                        int x, int y, bmp_type *mouse, bmp_type *below)
{
  /* read hidden pixels */
  vga_rd_bitmap(vga_base, x, y, below);
  /* draw initial pointer  */
  vga_wr_bitmap(vga_base, x, y, mouse, 1);
}

/***********************************************************************
* function: vga_move_mouse_ptr()
* purpose:  move the mouse pointer by writing pointer bitmap
            to a new coordinate
* argument:
*   vga_base: base address of VGA video ram
*   ps2_base: base address of PS2 device
*   xold: current x-axis coordinate, 10 LSBs used
*   yold: current y-axis coordinate, 9 LSBs used
*   below: pointer to the buffer storing pixels below mouse pointer
*   xnew: current x-axis coordinate, 10 LSBs used
*   ynew: current y-axis coordinate, 9 LSBs used
*   mouse: pointer to mouse pointer bitmap
*   mv: pointer to mouse activity data
* return:
*   - 1 if mouse has activities; 0 otherwise
*   - new mouse pointer coordinates: xnew, ynew
*   - mouse activity data: mv
*   - underlying pixels at (xnew,ynew) are stored into below buffer
* note:
*   - the calling function must allocate memory for "below" buffer
***********************************************************************/
int vga_move_mouse_ptr(alt_u32 vga_base,  alt_u32 ps2_base,
       int xold, int yold, bmp_type *below, int *xnew, int *ynew,
       bmp_type *mouse, mouse_mv_type *mv)
{
  if (mouse_get_activity(ps2_base, mv)==0)  // no movement
    return(0);
  /* calculate new mouse pointer position */
  *xnew = xold + mv->xmov;
  if (*xnew > (639 - mouse->width))
    *xnew = 639- mouse->width;
  if (*xnew<0)
    *xnew=0;
  *ynew = yold - mv->ymov;                  // VGA y-axis goes downward
  if (*ynew>(479 - mouse->height))
    *ynew = 479 - mouse->height;
  if (*ynew<0)
    *ynew=0;
  /* draw the updated mouse pointer, restore "under" area  */
  vga_move_bitmap(vga_base, xold, yold, below, *xnew, *ynew, mouse);
  return(1);
}


/***********************************************************************
* function: proc_mouse()
* purpose:  process mouse activities
* argument:
*   vga_base: base address of VGA video ram
*   ps2_base: base address of PS2 mouse
*   sw_base: base address of switches
*   btn_base: base address of push buttons
*   *cx0: initial cx value in Q4.28 (left bottom point in cx-cy plane)
*   *cy0: initial cy value in Q4.28 (left bottom point in cx-cy plane)
*   *delta: value between two successive points in fractal in Q4.28
*   *max_itr: max number of iterations
*   *engine: engine used (0 for software; 1 for accelerator)
* return:
*   update values of cx0, cy0, delta, max_itr, engine
* note:
*   - function exits when clicking on "start drawing"
***********************************************************************/
void proc_mouse(alt_u32 vga_base, alt_u32 ps2_base, alt_u32 sw_base,
                fixed428 *cx0, fixed428 *cy0, fixed428 *delta,
                int *max_itr, int *engine)
{
  alt_u32 sw;
  /* fractal related variables */
  static int zoom = 0;
  static int mitr = 30;
  static fixed428 cx_c = 0xf8000000;  // center of cx axis
  static fixed428 cy_c = 0x00000000;  // center of cy axis
  fixed428 cx_c_new, cy_c_new, delta_old, delta_new;
  /* mouse pointer related variables */
  static int px = 240;   // x coordinate of mouse
  static int py = 240;   // y coordinate of mouse
  int act, px_new, py_new;
  mouse_mv_type mv;
  /* mouse pointer pixel buffer */
  static alt_u8 bdata[20*12];
  bmp_type below={12, 20, bdata};

  delta_old = (WD/480) >> zoom;   //delta of current graph
  delta_new = delta_old;          // for panel display
  cx_c_new = cx_c;
  cy_c_new = cy_c;

  /*  draw initial pointer */
  ps2_flush_fifo(ps2_base);
  vga_init_mouse_ptr(vga_base, ps2_base, px, py,&MOUSE_BMP, &below);

  while (1){
    act = vga_move_mouse_ptr(vga_base, ps2_base, px, py, &below,
                             &px_new, &py_new, &MOUSE_BMP, &mv);
    if (act){
      px = px_new;
      py = py_new;
      if(mv.lbtn){ /* left button pressed */
      sw = pio_read(sw_base);
         /* update parameters according to mouse pointer position */
         if (px<480){                        // in drawing area,
           /* set new center of drawing */
           cx_c_new = cx_c + delta_old*(px-240);
           cy_c_new = cy_c + delta_old*(240-py);
           printf("center:(%+2.6f, %+2.6f) \n",
                   f2f(cx_c_new), f2f(cy_c_new));
         }
         if (px>480 && 16<=py && py<32){     // in "load zoom" area
           if (sw>20)
              sw = 20;
           zoom = sw;
           delta_new = (WD/480)>>zoom;
           printf("zoom factor: %d (2^%d)\n", 1<<zoom, zoom);
         }
         if (px>480 && 32<=py && py<48){     // in "load max_itr" area
           mitr = (sw & 0x000003ff)*10;
           if (mitr>4095)
             mitr=4095;
           printf("max iteration: %d\n", mitr);
         }
         if (px>480 && 48<=py && py<64){     // in "select engine" area
           *engine = sw & 0x00000001;
           printf("engine #: %d\n", *engine);
         }
         if (px>480 && 64<=py && py<80){     // in "restore initial" area
           *engine = 0;
           zoom = 0;
           delta_new = (WD/480) >> zoom;
           mitr = 30;
           cx_c_new = 0xf8000000;  // -0.5 in Q4.28
           cy_c_new = 0x00000000;  //  0.0 in Q4.28
         }
         if (px>480 && 80<=py && py<96){     // in "start drawing" area
           printf("start drawing\n\n");
           break;
         }
         disp_param(vga_base, cx_c_new, cy_c_new, delta_new,
                    zoom, mitr, *engine);
      } // end if (mv.lbtn)
    } // end if (act)
  } // end while
  /* update fractal parameters */
  cx_c = cx_c_new;
  cy_c = cy_c_new;
  *delta = delta_new;
  *max_itr = mitr;
  *cx0 = cx_c_new - delta_new*240;
  *cy0 = cy_c_new - delta_new*(479-240);
  // restore image below mouse
  vga_wr_bitmap(vga_base, px, py, &below, 0);
}

/***********************************************************************
* function: main()
* purpose:  Draw fractal on VGA screen with mouse/switch interface
* note:
***********************************************************************/
int main(void)
{
  fixed428 cx0 = 0xe0000000;           // -2 in Q4.28
  fixed428 cy0 = 0xe8000000;           // -1.5 in Q4.28
  fixed428 delta = WD/FPIX;
  int max_itr = 30;
  int engine = 0;
  alt_u8 frac_msg[4]={sseg_conv_hex(15), 0x2f, 0x27, sseg_conv_hex(1)};

  sseg_disp_ptn(SSEG_BASE, frac_msg);     // show "Frcl" for Fractal
  printf("Fractal test \n\n");
  vga_clr_screen(VRAM_BASE,0);
  disp_msg(VRAM_BASE);
  disp_param(VRAM_BASE, cx0+240*delta, cy0+240*delta, delta,
             0, max_itr, engine);
  draw_fractal(VRAM_BASE, 0, engine, cx0, cy0, delta, max_itr);
  mouse_init(PS2_BASE);
  while (1){
    proc_mouse(VRAM_BASE, PS2_BASE, SWITCH_BASE,
               &cx0, &cy0, &delta, &max_itr, &engine);
    draw_fractal(VRAM_BASE, F_ENGINE_BASE, engine,
                 cx0, cy0, delta, max_itr);
  }
}



