
#include "libc.h"
#include "minimp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "hpss.h"
#include <math.h>





int main(int argc, char *argv[]) {
    mp3_decoder_t mp3;
    mp3_info_t info;

    //mp3
    int fd;
    void *file_data;
    unsigned char *stream_pos;
    signed short sample_buf[MP3_MAX_SAMPLES_PER_FRAME];
    int bytes_left;
    int frame_size;

    printf("minimp3 -- a small MPEG-1 Audio Layer III player based on ffmpeg\n\n");
    if (argc < 2) {
        printf("Error: no input file specified!\n");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("Error: cannot open `");
        printf(argv[1]);
        printf("'!\n");
        return 1;
    }

    // drain the input fifo of any left over cruft
    unsigned int buffer_size=44100*10;
    FILE * pFile;
      pFile = fopen ("/www/pages/Audio2.bin","wb");
      if (pFile==NULL)
      {
          printf("Could not open the file... duck\n");
          return 0;
      }

    bytes_left = lseek(fd, 0, SEEK_END);
    file_data = mmap(0, bytes_left, PROT_READ, MAP_PRIVATE, fd, 0);
    stream_pos = (unsigned char *) file_data;
    bytes_left -= 100;
    printf("Now Playing: ");
    printf(argv[1]);

    mp3 = mp3_create();
    frame_size = mp3_decode(mp3, stream_pos, bytes_left, sample_buf, &info);
    printf("Sampe Rate %d, NumChannels %d, BytesPerFrame %d\n",info.sample_rate,info.channels,info.audio_bytes);
    if (!frame_size) {
        printf("\nError: not a valid MP3 audio file!\n");
        return 1;
    }


    //Set argument for the Div_freq and number of channels
//
//	value = AFMT_S16_LE;
//	    if (ioctl(pcm, SNDCTL_DSP_SETFMT, &value) < 0)
//	        FAIL("cannot set audio format");
//
//	    if (ioctl(pcm, SNDCTL_DSP_CHANNELS, &info.channels) < 0)
//	        FAIL("cannot set audio channels");
//
//	    if (ioctl(pcm, SNDCTL_DSP_SPEED, &info.sample_rate) < 0)
//	        FAIL("cannot set audio sample rate");
//
//	    printf("\n\nPress Ctrl+C to stop playback.\n");


    //saving mp3 file into a bin file
    //use audacity to import the data as raw data
    //Signed Data 8 bits
    //little endian
    //1 Channels
    int hoh=0;

    signed short readdata=0;
        while ((bytes_left >= 0) && (frame_size > 0)) {
            stream_pos += frame_size;
            bytes_left -= frame_size;
            for(hoh=0; hoh<info.audio_bytes/2; hoh++){
                readdata=sample_buf[hoh];
                readdata=((readdata>>8)&0xff);
                if(hoh%2){//Left Channel
                    fwrite ((const void *)&readdata ,sizeof(char),1,pFile);
                }
                else {//right channel

                }
                //fifo32_write(&input,readdata);
            }

            frame_size = mp3_decode(mp3, stream_pos, bytes_left, sample_buf, NULL);
        }


        fclose (pFile);



    close_ports();
}


