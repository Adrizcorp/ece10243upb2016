/***********************************************************************
*
* Module:  BMP file retrieval test
* File:    chu_main_bmp_file_test.c
* Purpose: Test BMP (.bmp) file access and demonstrate simple animation
* IP core base addresses:
*    - SWITCH_BASE: slide switch
*    - VRAM_BASE: video SRAM
*
***********************************************************************/
/* file inclusion */
#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "chu_avalon_gpio.h"
#include "chu_avalon_vga.h"
#include "chu_avalon_file.h"

/* constants */
#define  BMP_FILE_NAME  "/mnt/host/earth9.bmp"  // path and file name
#define  NF 9                                   // # of frames
#define  NW 100                                 // width of a frame
#define  NH 100                                 // height of a frame

/***********************************************************************
* function: read_bmp_file()
* purpose:  read bitmap from BMP file and store it in a buffer
* argument:
*   file_name: name of the BMP file
*   buf: pointer to bitmap buffer
* return: 0 if successful
* note:
*   - calling function must allocate buffer space
*   - only 24-bit BMP file is supported
*   - 24-bit color is converted to 8-bit color
***********************************************************************/
int read_bmp_file(char *file_name, bmp_type *buf)
{
  FILE *fp;
  int color_bit, x, y, slack;
  alt_u8 pixr, pixg, pixb, pix;

  /* open the file */
  fp = fopen(file_name,"rb");
  if (fp==NULL){
    printf("Error: %s fails to open. \n", file_name);
    return(-1);
  }
  /* check "magic number"; should be BM */
  if (fgetc(fp)!='B' || fgetc(fp)!='M'){
    printf("Error: %s is not a .bmp file.\n", file_name);
    fclose(fp);
    return(-1);
  }
  fskip(fp,16);                       // offset 2
  /* get height and width */
  buf->width  = (int) fget32(fp);     // offset 18
  buf->height = (int) fget32(fp);     // offset 22
  fskip(fp,2);                        // offset 26
  /* check color depth; should be 24 */
  color_bit = (int) fget16(fp);       // offset 28
  if (color_bit != 24){
    fclose(fp);
    printf("Error: color depth is not 24. \n");
    return(-2);
  }
  /* 24-bit BMP file format confirmed */
  printf("File opened. Bitmap width: %d, height: %d\n",
          buf->width, buf->height);
  fskip(fp,24);                       // offset 30
  printf("Reading in progress: \n");
  /* loop through pixel data, staring with the bottom row */
  for (y=buf->height-1; y >= 0; y--){ // offset 54
    printf(".");
    for (x=0; x< buf->width; x++) {
      /* get 24-bit color */
      pixb = (alt_u8) fgetc(fp);
      pixg = (alt_u8) fgetc(fp);
      pixr = (alt_u8) fgetc(fp);
      /* construct 8-bit color using MSBs */
      pix = (pixr & 0xe0) + ((pixg & 0xe0)>>3) + ((pixb & 0xc0)>>6);
      buf->pdata[y*(buf->width)+x]=pix;
    }  //end for x
    /* skip padding bytes, if exist */
    slack = (buf->width * 3) % 4;
    if (slack!=0)
      fskip(fp,4-slack);
  } //end for y
  fclose(fp);
  printf("\nFile loaded.\n");
  return(0);
}

/***********************************************************************
* function: main()
* purpose:  Read a "earth" bitmap file and demonstrate simple animation
* note:
*   - the host file feature must be enabled in BSP editor
*   - the earth9.bmp bitmap file should be in the project directory
*   - build/load the program with "Debug As => Nios II Hardware"
***********************************************************************/
int main(void)
{
  alt_u8 iarray[NF*NH*NW];         // pixel data array for file buffer
  alt_u8 farray[NF][NH*NW];        // pixel data array for frames
  bmp_type img={NF*NW, NH, iarray};
  bmp_type frame[NF];
  int sw, status;
  int f, x, y;

  printf("BMP file retrieval test. \n\n");
  vga_clr_screen(VRAM_BASE, 0x08);
  status = read_bmp_file(BMP_FILE_NAME, &img);
  if (status!=0){
    printf("BMP file fails to load.  Exit program. \n");
    exit(1);
  }
  /* split bitmaps to 9 frames */
  for (f=0; f<NF; f++){
    frame[f].height = NH;
    frame[f].width = NW;
    frame[f].pdata = farray[f];
    for (y=0; y<NH; y++) {
      for (x=0; x<NW; x++) {
        frame[f].pdata[y*NW+x]=img.pdata[y*NW*NF+f*NW+x];
      } // end x loop
    } // end y loop
  } //end f loop

  /* display individual frames in two rows  */
  for (f=0; f<5; f++)
    vga_wr_bitmap(VRAM_BASE, 30+f*(20+NW), 10, &frame[f], 1);
  for (f=5; f<9; f++)
    vga_wr_bitmap(VRAM_BASE, 80+(f-5)*(20+NW), 120, &frame[f], 1);

  /* animation of rotating earth  */
  while(1){
    for (f=0; f<NF; f++){
    sw = pio_read(SWITCH_BASE); ;
      if (sw!=0){            // freeze if sw=0
        usleep(1000000/sw);  // sw frames per second
        vga_wr_bitmap(VRAM_BASE, 270, 250, &frame[f],1);
      } // end if
    } // end for
  } // end while
}
