/***********************************************************************
*
* Module:  SD card and FAT test
* File:    chu_main_sd_test.c
* Purpose: Test SD card access
* IP core base addresses:
*    - SWITCH_BASE: slide switch
*    - BTN_BASE: pushbutton
*    - SSEG_BASE: 7-segment LED display
*    - SDC_BASE: SD card controller
*
***********************************************************************/
/* file inclusion */
#include <stdio.h>
#include "system.h"
#include "chu_avalon_gpio.h"
#include "chu_avalon_sd.h"

/***********************************************************************
* function: print_sector()
* purpose: print a 512-byte sector in hex/ascii table
* argument:
*   buf: pointer to the 512-byte buffer
* return:
* note:
***********************************************************************/
/* print a 512-byte sector in hex and ASCII format */
void print_sector(alt_u8 *buf)
{
  int i, j;
  alt_u8 ch;

  for (j=0; j<32; j++){
    printf("0x%02x-  ", j);
    for (i=0; i <16; i++)
      printf("%02x ", buf[j*16+i]);
    printf("  ");
    for (i=0; i <16; i++){
      ch = buf[j*16+i];
      if (ch>127 || ch<32)   // non ascii
        ch = '.';
      printf("%c", ch);
    } // end for i
    printf("\n");
  } //end for j
  printf("\n");
}

/***********************************************************************
* function: main()
* purpose: test SD card and FAT16
* note:
***********************************************************************/
int main(void)
{
  fat_para_type fat;
  file_dp_type fd;
  char fname[15], yes[3];
  int sw, btn;
  unsigned int num;
  int i, j, s, status, sdhc;
  alt_u32 sect;
  alt_u8 ch, dvsr;
  alt_u8 rbuf[512], wbuf[512];   // read and write buffers
  alt_u8 disp_msg[4]={sseg_conv_hex(5), sseg_conv_hex(13),
                      0xff, sseg_conv_hex(12)};

  sseg_disp_ptn(SSEG_BASE, disp_msg);      // show "Sd C" for display
  printf("SD card FAT16 file system test:\n");
  sdhc=sd_init(SDC_BASE);
  if (sdhc==-1)
     printf("SD card initialization failed \n");
  btn_clear(BTN_BASE);
  while (1){
    while (!btn_is_pressed(BTN_BASE)){ };          // wait for button
    btn=btn_read(BTN_BASE);                        // read button
    if (btn & 0x02){                               // key1 pressed
      sw=pio_read(SWITCH_BASE);                    // read switch
      // printf("key/sw: %d/%d\n", btn, sw);
    }
    btn_clear(BTN_BASE);
    switch (sw){
      case 0:  // mount FAT16 file system
        status=sd_file_mount(SDC_BASE, &fat);
        sdhc = fat.sdhc;
        if (status==0) {
          printf("FAT 16 mounted on SD card\n");
          printf("starting FAT table sector: %d\n", fat.fat0);
          printf("starting root dir sector:  %d\n", fat.rdir0);
          printf("starting data sector:      %d\n", fat.data0);
          printf("sectors per cluster:       %d\n", fat.cls_size);
          printf("clusters in data segment:  %d\n", fat.data_size);
          printf("file entries of root dir:  %d\n\n", fat.rdir_size);
        } else
          printf("Mount failed: status=%d\n\n", status);
      break;
      case 1:  // open a file
        printf("Enter file name in 8.3 format: ");
        scanf("%s", fname);
        status=sd_file_fopen(&fat, fname, &fd);
        if (status==0) {
          printf("\nFile open successful.\n");
          printf("file size (bytes): %d\n", fd.size);
          printf("root dir entry #:  %d\n", fd.rdir_index);
          sect = fat.rdir0 + fd.rdir_index/32;
          printf("entry sector #:    %d\n", (int)sect);
          printf("starting cluster#: %d\n", fd.cls0);
          sect = fat.data0 + (fd.cls0-2)*fat.cls_size;
          printf("starting sector #: %d\n\n", (int)sect);
        } else
          printf("\nFile open failed: status=%d\n\n", status);
        break;
      case 2:  // read file and list first 2 and last 2 sectors
        s = fd.size/512;
        if ((fd.size%512)!=0)  // fraction of a segment
          s++;
        printf("File size (bytes/sectors): %d/%d\n", fd.size, s);
        printf("Data dump for first 2 and last 2 sectors:\n\n");
        for (i=0; i<s; i++){
          for (j=0; j<512; j++){
           sd_file_read_byte(&fat, &fd, &ch);
             rbuf[j]=ch;
           }
          if (i<2 || i>s-3){
            printf("sector %d of file:\n", i);
            print_sector(rbuf);
          } else {
            printf(".");
          } // end if
        } // end for i
        break;
      case 3: // read and print a 512 byte sector
        printf("Enter sd card read sector number: ");
        scanf("%u", &num);
        sect = (alt_16) num;
        status=sd_read_sector(SDC_BASE, sdhc, sect, rbuf);
        if (status!=0)
          printf("read sd card failed\n\n");
        else{
          printf("\nsector %d(0x%x)\n", (int)sect, (int)sect);
          print_sector(rbuf);
        }
        break;
      case 4: // write a 512 byte sector
        printf("Low-level sector write may corrupt file system.\n");
        printf("Press Y to continue: ");
        scanf("%s", yes);
        if (yes[0]!='y' && yes[0]!='Y'){
          printf("Sector write abandoned.\n\n");
          break;
        }
        printf("Enter sd card write sector number: ");
        scanf("%u", &num);
        sect = (alt_16) num;
        for (i=0; i<512; i++)
          wbuf[i] = (alt_u8) (sect + i);
        status=sd_write_sector(SDC_BASE, sdhc, sect, wbuf);
        if (status!=0)
          printf("Write sd card failed\n\n");
        else
          printf("write sd card completed\n\n");
        break;
      case 5:  // set frequency divisor of SPI clock
        printf("Enter frequency divisor (1-255): ");
        scanf("%u", &num);
        dvsr = (alt_u8) num;
        sd_spi_wr_dvsr(SDC_BASE, dvsr);
        printf("SPI bus frequency set to %6.3f MHz.\n\n", 50.0/(2.0*dvsr));
        break;
      case 6:  // reinitialize SD card
        sdhc=sd_init(SDC_BASE);
        if (sdhc==-1)
          printf("SD card initialization failed.\n\n");
        else
          printf("SD card initialized (sdhc status=%d).\n\n", sdhc);
        break;
    } //end switch
  } // end while
}
