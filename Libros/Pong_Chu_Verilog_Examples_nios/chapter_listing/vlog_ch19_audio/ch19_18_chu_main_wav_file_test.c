/***********************************************************************
*
* Module:  WAV file retrieval test
* File:    chu_main_wav_file_test.c
* Purpose: Test wave (.wav) file access
* IP core base addresses:
*    - AUDIO_BASE: audio codec controller
*
***********************************************************************/
/* file inclusion */
#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "chu_avalon_file.h"
#include "chu_avalon_audio.h"

/* constants */
#define  WAV_FILE_NAME  "/mnt/host/trumpet.wav" // path and file name
#define  BUF_SIZE       (6*48000)               // 6 sec of audio data

/***********************************************************************
* function: read_wav_file()
* purpose:  read audio data from wave file and store it in a buffer
* argument:
*   file_name: name of the WAV file
*   buf: pointer to bitmap buffer
* return:
*   - 0: if successful
*   - buf updated with audio data
* note:
*   - calling function must allocate buffer space
*   - only support the following format:
*       - compression: 1 (PCM)
*       - channel: 2
*       - sampling rate: 48K
*       - resolution: 16 bits
***********************************************************************/
int read_wav_file(char *file_name, alt_u32 *buf)
{
  /* note that fget32 read in little endian, but id in big endian */
  const alt_u32 RIFF_ID = 0x46464952;     //ascii for FFIR
  const alt_u32 WAVE_ID = 0x45564157;     //ascii for EVAW
  const alt_u32 FMT_ID  = 0x20746d66;     //ascii for \btmf
  const alt_u32 DATA_ID = 0x61746164;     //ascii for ATAD

  FILE *fp;
  alt_u32 r_id, w_id, f_id, d_id, srate, data_size;
  alt_u16 compression, channel, res;
  int i, s_size;

  /* open the file */
  fp = fopen(file_name,"rb");
  if (fp==NULL){
    printf("Error: cannot open file %s.\n", file_name);
    return(-1);
  }
  /* extract relevant chunk/subchunk info */
  r_id = fget32(fp);          // offset  0: "RIFF" chunk id
  fskip(fp,4);                // offset  4: chunk size
  w_id = fget32(fp);          // offset  8: "WAVE" chunk id
  f_id = fget32(fp);          // offset 12: "fmt " subchunk id
  fskip(fp,4);                // offset 16: subchunk size
  compression=fget16(fp);     // offset 20: 1 for PCM
  channel = fget16(fp);       // offset 22: 2 for stereo
  srate = fget32(fp);         // offset 24: 48K sampling rate
  fskip(fp,4);                // offset 28: byte rate
  fskip(fp,2);                // offset 32: block size
  res = fget16(fp);           // offset 34: 16 bits resolution
  d_id = fget32(fp);          // offset 36: "data" subchunk id
  data_size = fget32(fp);     // offset 40: # bytes of data subchunk
  /* check chunk/subchunk ids and parameters */
  if ((r_id!=RIFF_ID) || (w_id!=WAVE_ID)  || (f_id!=FMT_ID) ||
      (d_id!=DATA_ID) || (compression!=1) || (channel!=2)   ||
      (srate!=48000)  || (res!=16)){
    printf("Error: incorrect wave file format\n");
    printf("Must be PCM, 2 channels, 48K rate, 16-bit resolution.\n");
    printf("RIFF/WAVE/fmt/data ids: %08x/%08x/%08x/%08x\n",
           r_id, w_id, f_id, d_id);
    printf("compression/channel/srate/res/d_szie: %d/%d/%d/%d/%d\n",
            compression, channel, srate, res, data_size);
    fclose(fp);
    return(-1);
  }
  s_size = data_size/4;
  printf("File opened.\n # audio data samples: %d\n", s_size);
  /*if (s_size > BUF_SIZE);
     s_size = BUF_SIZE;  */
  for (i=0; i<s_size; i++) {
    // get 32-bit data
    buf[i] = fget32(fp);
    if (i%1000 == 0)
      printf(".");
  }
  fclose(fp);
  printf("\nFile loaded.\n");
  return(0);
}

/***********************************************************************
* function: main()
* purpose:  Read a wave file and play it back
* note:
*   - the host-based file system must be enabled in BSP editor
*   - the trumpet.wav sound file should be in the project directory
*   - build/load the program with "Debug As => Nios II Hardware"
***********************************************************************/
int main(void){
  alt_u32 buf[BUF_SIZE];
  int i;

  audio_init(AUDIO_BASE);
  printf("Wave file test \n\n");
  if (read_wav_file(WAV_FILE_NAME, buf)!=0){
    printf("\n Fail to load wav file. \n");
    return (0);
  }
  while(1){
    for(i=0; i<BUF_SIZE; i++){
      while(audio_dac_fifo_full(AUDIO_BASE)){}  // wait if dac fifo full
        audio_dac_wr_fifo(AUDIO_BASE, buf[i]);
    } // end for
  } // end while
}