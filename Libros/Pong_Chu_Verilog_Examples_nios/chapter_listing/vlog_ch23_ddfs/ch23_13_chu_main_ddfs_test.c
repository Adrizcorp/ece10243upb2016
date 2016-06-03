/***********************************************************************
*
* Module:  ddfs test
* File:    chu_main_ddfs_test.c
* Purpose: Test audio frequency DDFS
* IP core base addresses:
*    - SWITCH_BASE: switch
*    - BTN_BASE: pushbutton
*    - SSEG_BASE: 7-segment LED
*    - D_ENGINE_BASE: ddfs
*    - AUDIO_BASE: audio codec
*
***********************************************************************/
/* file inclusion */
#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "chu_avalon_gpio.h"
#include "chu_avalon_ddfs.h"

/***********************************************************************
 * function: ddfs_play_siren1()
 * purpose:  play two-frequency (600/900 Hz) siren for few seconds
 * argument:
 *   ddfs_base: base address of ddfs
 * return:
 * note:
 ***********************************************************************/
void ddfs_play_siren1(alt_u32 ddfs_base)
{
  int i;

  ddfs_wr_carrier_freq(ddfs_base, 600);    // 600 Hz carrier
  for (i=0; i<10; i++){                    // 10 cycles
    ddfs_wr_offset_freq(ddfs_base, 0);     // 0 Hz offset
    usleep(300*1000);                      // 300 ms
    ddfs_wr_offset_freq(ddfs_base, 300);   // 300 Hz offset
    usleep(300*1000);                      // 300 ms
  }
  ddfs_wr_carrier_freq(ddfs_base, 0);
  ddfs_wr_offset_freq(ddfs_base, 0);
}

/***********************************************************************
 * function: ddfs_play_siren2()
 * purpose:  play sweeping-frequncy (800-2000 Hz) siren for few seconds
 * argument:
 *   ddfs_base: base address of ddfs
 * return:
 * note:
 ***********************************************************************/
void ddfs_play_siren2(alt_u32 ddfs_base)
{
  int i, j;

  ddfs_wr_carrier_freq(ddfs_base, 800);
  for (i=0; i<10; i++){                     // 10 cycles
    for (j=0; j<30; j++){                   // sweep 30 steps
      ddfs_wr_offset_freq(ddfs_base, j*40); // 40 Hz increment
      usleep(25*1000);                      // 25 ms
    } // end j loop
  } // end i loop
  ddfs_wr_carrier_freq(ddfs_base, 0);
  ddfs_wr_offset_freq(ddfs_base, 0);
}

/***********************************************************************
 * function: ddfs_set_note()
 * purpose:  set ddfs frequency for a music note
 * argument:
 *   ddfs_base: base address of ddfs
 *   oct: octave from 0 to 9 (16 to 16K Hz; "middle" is 4)
 *   ni: note index 0 to 11 (C, C#, D, D#, ..., to B)
 * return:
 * note:
 *  - 1st octave frequencies listed in a look-up table
 *  - corresponding note freq in octave n: f*2^n
 *  - listening to low- and high- octave freq needs good audio amp
 ***********************************************************************/
void ddfs_set_note(alt_u32 ddfs_base, int oct, int ni)
{
  // frequency table for octave 0
  // octave n: f*2^n
  const float NOTES[]={
    16.3516,   //  0 C
    17.3239,   //  1 C#
    18.3541,   //  2 D
    19.4454,   //  3 D#
    20.6017,   //  4 E
    21.8268,   //  5 F
    23.1247,   //  6 F#
    24.4997,   //  7 G
    25.9565,   //  8 G#
    27.5000,   //  9 A
    29.1352,   // 10 A#
    30.8677    // 11 B
  };
  alt_u32 freq;

  ddfs_wr_offset_freq(ddfs_base, 0);
  freq = NOTES[ni] * (1<<oct);          // NOTES[]*(2^oct)
  ddfs_wr_carrier_freq(ddfs_base, freq);
}

/***********************************************************************
 * function: ddfs_play_oct()
 * purpose:  play notes in octaves 3 to 6; 500 ms each
 * argument:
 *   ddfs_base: base address of ddfs
 * return:
 * note:
 ***********************************************************************/
void ddfs_play_oct(alt_u32 ddfs_base)
{
  int oct, ni;

  for (oct=3; oct<7; oct++){
    for (ni=0; ni<12; ni++){
      ddfs_set_note(ddfs_base, oct, ni);
      usleep(500*1000);
    } // end ni loop
  } // end oct loop
  ddfs_wr_carrier_freq(ddfs_base, 0);
}

/***********************************************************************
 * function: ddfs_play_piano()
 * purpose:  play notes in octaves 3 to 6 with piano adsr envelope
 * argument:
 *   ddfs_base: base address of ddfs
 * return:
 * note:
 ***********************************************************************/
void ddfs_play_piano(alt_u32 ddfs_base)
{
  int oct, ni;
  int i, estep;
  int atime, dtime, stime, rtime;
  alt_16 env, am1, am2, am3;

  atime=10;
  dtime=50;
  stime=400;
  rtime=40;
  am1=0x7f00;
  am2=am1*0.8;
  am3=am2*0.5;

  for (oct=3; oct<7; oct++){
    for (ni=0; ni<12; ni++){
      ddfs_set_note(ddfs_base, oct, ni);  // set note frequency
      env = 0;
      /* attack region */
      estep = am1/atime;
      for (i=0; i<atime; i++){
        env = env + estep;
        usleep(1000);
        ddfs_wr_env(ddfs_base, env);
      }
      /* decay region */
      estep = (am1-am2)/dtime;
      for (i=0; i<dtime; i++){
        env = env - estep;
        usleep(1000);
        ddfs_wr_env(ddfs_base, env);
      }
      /* sustain region */
      estep = (am2-am3)/stime;
      for (i=0; i<stime; i++){
        env = env - estep;
        usleep(1000);
        ddfs_wr_env(ddfs_base, env);
      }
      /* release region */
      estep = am3/rtime;
      for (i=0; i<rtime; i++){
        env = env - estep;
        usleep(1000);
        ddfs_wr_env(ddfs_base, env);
      }
     } // end ni loop
  } // end oct loop
  ddfs_wr_carrier_freq(ddfs_base, 0);
  ddfs_wr_env(ddfs_base, 0x7fff);
}

/***********************************************************************
* function: main()
* purpose:  test audio frequency ddfs
* note:
***********************************************************************/
int main(void)
{
  int sw, btn, freq;
  alt_u8 disp_msg[4]={sseg_conv_hex(13), sseg_conv_hex(13),
                      sseg_conv_hex(15), sseg_conv_hex(5)};

  sseg_disp_ptn(SSEG_BASE, disp_msg);      // show "ddFS" for display
  ddfs_init(AUDIO_BASE, D_ENGINE_BASE);
  btn_clear(BTN_BASE);
  printf("DDFS test \n\n");

  while (1){
    while (!btn_is_pressed(BTN_BASE)){ };          // wait for button
    btn=btn_read(BTN_BASE);                        // read button
    if (btn & 0x02){                               // key1 pressed
      sw=pio_read(SWITCH_BASE);                    // read switch
      printf("key/sw: %d/%d\n", btn, sw);
    }
    btn_clear(BTN_BASE);
    switch (sw){
      case 0:
        ddfs_init(AUDIO_BASE, D_ENGINE_BASE);
        break;
      case 1:  // set ddfs frequency
        printf("enter frequency:");
        scanf("%d", &freq);
        ddfs_wr_carrier_freq(D_ENGINE_BASE, freq);
        break;
      case 2:  // play siren 1
        ddfs_play_siren1(D_ENGINE_BASE);
        break;
      case 3:  // play siren 2
        ddfs_play_siren2(D_ENGINE_BASE);
        break;
      case 4:  // play 6 octaves without envelope
        ddfs_play_oct(D_ENGINE_BASE);
        break;
      case 5:  // play 6 octaves with piano adsr envelope
        ddfs_play_piano(D_ENGINE_BASE);
        break;
     }  //end switch
   } // end while
 }

