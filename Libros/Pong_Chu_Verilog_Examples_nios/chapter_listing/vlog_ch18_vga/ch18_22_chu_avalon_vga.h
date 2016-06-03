/***********************************************************************
*
* Module:  VGA video driver header
* File:    chu_avalon_vga.h
* Purpose: Routines to access video SRAM and display bit-mapped graphics
*          and text
*
************************************************************************
*  Register map
************************************************************************
* Read (data to cpu):
*   offset 0x00000 to 0x7ffff
*     * bit 7-0: 8-bit color
*   offset 0x80000
*     * bit 9-0:   VGA scan's current x (horizontal) position
*     *- bit 19-10: VGA scan's current y (vertical) position
* Write (data from cpu):
*   offset 0x00000 to 0x7ffff
*     * bit 7-0: 8-bit color
***********************************************************************/
/* file inclusion */
#include <alt_types.h>

/***********************************************************************
* Data type definitions
***********************************************************************/
/* data type for a bitmap */
typedef struct tag_bmp
{
  int width;
  int height;
  alt_u8 *pdata;   //  pointer to pixel array
} bmp_type;

/***********************************************************************
* constant definitions
***********************************************************************/
#define DISP_GRF_X_MAX  640                 // 640 columns (0 to 639)
#define DISP_GRF_Y_MAX  480                 // 480 rows    (0 to 479)

/***********************************************************************
* Function prototypes
***********************************************************************/
/* Video memory access */
alt_u32 vga_calc_sram_addr(int x, int y);
alt_u8 vga_rd_pix(alt_u32 vga_base, int x, int y);
void vga_rd_xy(alt_u32 vga_base, int *x, int *y);
void vga_wr_pix(alt_u32 vga_base, int x, int y, alt_u8 color);
/* Plotting and clear */
void vga_plot_line(alt_u32 vga_base, int x1, int y1,
                    int x2, int y2, alt_u8 color);
void vga_clr_screen(alt_u32 vga_base, alt_u8 color);
/* Bitmap processing */
void vga_wr_bitmap(alt_u32 vga_base, int x, int y,
                    bmp_type *bmp, int tran);
void vga_rd_bitmap(alt_u32 vga_base, int x, int y, bmp_type *bmp);
void vga_move_bitmap(alt_u32 vga_base,
                      int xold, int yold, bmp_type *below,
                      int xnew, int ynew, bmp_type *bmp);
/* Bit-mapped text */
void vga_wr_bit_ch(alt_u32 vga_base, int x, int y,
                    char ch, int color, int zoom);
void vga_wr_bit_str(alt_u32 vga_base, int x, int y,
                     char *s, int color, int zoom);

