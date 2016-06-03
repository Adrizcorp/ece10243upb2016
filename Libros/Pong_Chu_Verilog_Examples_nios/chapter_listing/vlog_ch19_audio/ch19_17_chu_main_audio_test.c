/***********************************************************************
*
* Module:  Audio codec test
* File:    chu_main_audio_test.c
* Purpose: Test audio codec driver routines
* IP core base addresses:
*    - SWITCH_BASE: slide switch
*    - BTN_BASE: pushbutton
*    - SSEG_BASE: 7-segment LED
*    - VRAM_BASE: video SRAM
*    - AUDIO_BASE: audio codec controller
*
***********************************************************************/
/* file inclusion */
#include <stdio.h>
#include <math.h>     // for sin()
#include <unistd.h>
#include "system.h"
#include "chu_avalon_gpio.h"
#include "chu_avalon_audio.h"
#include "chu_avalon_vga.h"

/***********************************************************************
* function: record_sin_wave()
* purpose:  generate sin wave and record data points in buffer
* argument:
*   sf: sampling frequency
*   freq: sin wave frequency
*   size: size (# of data points) of the buffer
*   buf: pointer to the buffer
* return: updated buf with sin/cos data
* note:
*   - calling routine needs to allocate space for buffer
***********************************************************************/
void record_sin_wave(int sf, int freq, int size, alt_u32 *buf)
{
  const float PI=3.14159;
  const float AMP_MAX= 32767.0;        // max amplitude (2^15-1)
  float amp;
  int npoint, ncycle, i, j;
  alt_u32 left, right;

  npoint = sf/freq;                    // # of steps in one period
  /* construct 1st cycle */
  for (i=0; i<npoint; i++){
    amp = sin((float)i/(float)npoint * 2.0 * PI);
    left = (alt_u32) (amp * AMP_MAX);  // left channel; 16 LSBs used
    amp = cos((float)i/(float)npoint * 2.0 * PI);
    right = (alt_u32) (amp * AMP_MAX); // right channel; 16 LSBs used
    buf[i] = (left << 16) + right;     // combine two channels
  }
  /* duplicate the 1st cycle for the remaining ncycle-1 cycles */
  /* no data for the last fractional cycle                     */
  ncycle = size/npoint;
  for (j=1; j<ncycle; j++){
     for (i=0; i<npoint; i++){
        buf[j*npoint+i]=buf[i];
     } // end for i
  } // end for j
}

/***********************************************************************
* function: set_volume
* purpose:  set headphone volume
* argument:
*   audio_base: base address of audio codec controller
*   vol: volume
* return:
* note:
*   - codec: 7-bit headphone volume control; 80 levels in 1-dB step
*     0x7f: +6 dB;  0x79: 0 dB;  0x30: -73 dB;  <0x30: mute
***********************************************************************/
void set_volume(alt_u32 audio_base, int vol)
{
  alt_u16 cmd;

  if (vol>0x7f)                            // exceed maximal volume
     cmd = 0x007f;
  else
     cmd = (alt_u16) vol;
  while (!audio_i2c_is_idle(audio_base)){};
    audio_i2c_wr_cmd(audio_base, 2, cmd);  // left headphone out
  while (!audio_i2c_is_idle(audio_base)){};
    audio_i2c_wr_cmd(audio_base, 3, cmd);  // right headphone out
}

/***********************************************************************
* function: plot_audio_buffer()
* purpose:  plot buffered audio data on screen
* argument:
*   vga_base: base address of VGA video SRAM
*   buf: pointer to the buffer
* return:
* note:
*   - plot only the first 640 data points
*   - magnitude range is from -128 to +127
***********************************************************************/
void plot_audio_buffer(alt_u32 vga_base, alt_u32 *buf)
{
  int i, j;
  alt_16 y_left, y_right;

  for(i=1; i<640; i++){
    y_right = (alt_16) (0x0000ffff ^ buf[i]); // right channel data
    y_left =  (alt_16) (buf[i]>>16);          // left channel data
    j=480 - ((int)y_left/256 + 480/2);        // adjust y to -128/127
    vga_wr_pix(vga_base, i, j, 0xe0);         // plot left channel red
    j=480 - ((int)y_right/256 + 480/2);       // adjust y to -128/127
    vga_wr_pix(vga_base, i, j, 0x03);         // plot right channel blue
  }
}

/***********************************************************************
* function: main()
* purpose:  test audio codec
* note:
***********************************************************************/
int main(void)
{
  const int SF=48000;       // sampling freq=48K
  const int BUF_SIZE= 5*SF; // 5 sec @ sampling frequency SF
  alt_u32 buf[BUF_SIZE];
  int sw, btn, freq, vol,  reg, cmd, i;
  alt_u8 disp_msg[4]={sseg_conv_hex(5), 0x23, 0x2b, sseg_conv_hex(13)};

  sseg_disp_ptn(SSEG_BASE, disp_msg);      // show "Sond" for display
  vga_clr_screen(VRAM_BASE,0);             // clear screen
  audio_init(AUDIO_BASE);
  btn_clear(BTN_BASE);
  printf("Audio codec interface test \n\n");

  while (1){
    while (!btn_is_pressed(BTN_BASE)){ };           // wait for button
    btn=btn_read(BTN_BASE);                         // read button
    if (btn & 0x02){                                // key1 pressed
      sw=pio_read(SWITCH_BASE);                     // read switch
      printf("key/sw: %d/%d\n", btn, sw);
    }
    btn_clear(BTN_BASE);
    switch (sw){
      case 0:  // initialize codec controller
        audio_init(AUDIO_BASE);
        break;
      case 1:  // record line input for 5 sec
        audio_i2c_wr_cmd(AUDIO_BASE, 4, 0x0010);    // line-in to adc
        for (i=0; i<BUF_SIZE; i++){
          while(audio_adc_fifo_empty(AUDIO_BASE)){} // wait if fifo empty
          buf[i]=audio_adc_rd_fifo(AUDIO_BASE);
        }
        break;
      case 2: // record microphone input for 5 sec
        audio_i2c_wr_cmd(AUDIO_BASE, 4, 0x0015);    // mic to adc, boost
        for(i=0; i<BUF_SIZE; i++){
          while(audio_adc_fifo_empty(AUDIO_BASE)){} // wait if fifo empty
          buf[i]=audio_adc_rd_fifo(AUDIO_BASE);
        }
        break;
      case 3:  // fill buffer with sinusoidal data
        printf("enter frequency:");
        scanf("%d", &freq);
        record_sin_wave(SF, freq, BUF_SIZE, buf);
        printf("sinusoidal wave recorded. \n");
        break;
      case 4: // play buffered audio data repeatedly until a key pressed
        while (!btn_is_pressed(BTN_BASE)){
          for(i=0; i<BUF_SIZE; i++){
            while(audio_dac_fifo_full(AUDIO_BASE)){} // wait if fifo full
            audio_dac_wr_fifo(AUDIO_BASE, buf[i]);
          } // end for
        } // end while
        break;
      case 5:  // issue codec command
         printf("enter codec register #:");
         scanf("%d", &reg);
         printf("enter command (in hex):");
         scanf("%x", &cmd);
         audio_i2c_wr_cmd(AUDIO_BASE, (alt_u8)reg, (alt_u16)cmd);
         printf("send 0x%x to codec register %d\n\n", cmd, reg);
         break;
      case 6:  // set volume
        printf("enter volume (between 28 and 127):");
        scanf("%d", &vol);
        set_volume(AUDIO_BASE, vol);
        printf("Volume set\n");
        break;
      case 7:  // plot buffered right- and left-channel data
        plot_audio_buffer(VRAM_BASE, buf);
        break;
      case 8:  // clear screen
        vga_clr_screen(VRAM_BASE,0);
        break;
     }  //end switch
   } // end while
 }



