/***********************************************************************
*
* Module:  SPI, SD card and FAT16 driver function prototypes
* File:    chu_avalon_sd.c
* Purpose: Routines to initialize and read/write SD card and
*          to read a file from FAT16 file system
*
***********************************************************************/
/* include section */
#include <stdio.h>        // for printf()
#include <io.h>
#include <ctype.h>        // for toupper() function
#include "chu_avalon_sd.h"

/***********************************************************************
*  SPI related functions
***********************************************************************/
/***********************************************************************
* function: sd_spi_is_ready()
* purpose:  check ready signal of SPI controller
* argument:
*   sd_base: base address of SD card interface
* return: 1: ready; 0: not ready
***********************************************************************/
int sd_spi_is_ready(alt_u32 sd_base)
{
  alt_u32 spi_reg;
  int spi_ready_bit;

  spi_reg = IORD(sd_base, CHU_SD_RD_DATA_REG);
  spi_ready_bit =  (int) ((spi_reg & 0x00000100) >> 8);
  return spi_ready_bit;
}

/***********************************************************************
* function: sd_spi_wr_cs()
* purpose:  enable or disable SD card's cs_n (ss) signal
* argument:
*   sd_base: base address of SD card interface
*   en_bit: 0 for enable; 1 for disable
* return:
***********************************************************************/
void sd_spi_wr_cs(alt_u32 sd_base, int en_bit)
{
  IOWR(sd_base, CHU_SD_CS_REG, (alt_u32) en_bit);
}

/***********************************************************************
* function: sd_spi_wr_dvsr()
* purpose:  write SPI clock divisor register
* argument:
*   sd_base: base address of SD card interface
*   dvsr: dvsr value (between 1 and 2^8-1)
* return:
* note:
*   - # system clocks in sclk period = 2*dvsr
*   - sclk freq = system clock freq / (2*dvsr)
*
***********************************************************************/
void sd_spi_wr_dvsr(alt_u32 sd_base, alt_u8 dvsr)
{
  IOWR(sd_base, CHU_SD_DVSR_REG, (alt_u32) dvsr);
}

/***********************************************************************
* function: sd_spi_wr_byte()
* purpose:  write a byte to SPI bus
* argument:
*   sd_base: base address of SD card interface
*   spi_data: 8-bit data
* return:
***********************************************************************/
void sd_spi_wr_byte(alt_u32 sd_base, alt_u8 spi_data)
{
  /* wait until SPI is ready */
  while (!sd_spi_is_ready(sd_base)){};
  /* write a byte */
  IOWR(sd_base, CHU_SD_WR_DATA_REG, (alt_u32) spi_data);
}

/***********************************************************************
* function: sd_spi_rd_byte()
* purpose:  read a byte from SPI bus
* argument:
*   sd_base: base address of sd card interface
* return: 8-bit data
* note:
*  - shift in/out are done simultaneously in SPI bus
*  - read/write are the same except that the input data is retrieved
*  - a dummy data is used for write
***********************************************************************/
alt_u8 sd_spi_rd_byte(alt_u32 sd_base)
{
  alt_u32 spi_reg;
  alt_u8 spi_data;

  /* write a dummy byte and shift in data as well */
  sd_spi_wr_byte(sd_base, 0xff);
  spi_reg = IORD(sd_base, CHU_SD_RD_DATA_REG);
  spi_data = (alt_u8) (spi_reg & 0x000000ff);
  return spi_data;
}

/************************************************************************
*  SD card related functions
************************************************************************/
/************************************************************************
* function: sd_wr_cmd()
* purpose:  send a command to sd card
* argument:
*   sd_base: base address of sd card interface
*   cmd: 6-bit command
*   argument: 32-bit argument
*   r3: 32-bit additional data for R3 and R5 responses
* return:
*   - response code (R1):
*       - 0xff when no response
*       - CMD0 (reset) command: 0x01 for no error
*       - other commands: 0x00 for no error; other for error conditions
* note:
*   - 6 bytes send: command + 4-byte argument (MSB first) + crc
*   - except for the CMD0/CMD8, crc is optional (not implemented)
*   - command format: 01 + 6-bit value
*   - sd card may need up to 8-byte transmission time to respond
*   - sd card continues sending 1 when busy (or no data)
*   - CMD8/CMD58 responds with 5 bytes
*
 ***********************************************************************/
alt_u8 sd_wr_cmd(alt_u32 sd_base, alt_u8 cmd, alt_u32 argument, alt_u32 *r3)
{
  int i;
  alt_u8 crc, rcode, byte;
  alt_u32 ocr=0;

  /* crc for CMD0 and CMD8 */
  if (cmd==SD_CMD0_RESET)
    crc=0x95;       // crc for CMD0(0)
  else
    crc =0x87;      // crc for CMD8(0x1aa)
  /* send command */
  sd_spi_wr_byte(sd_base, cmd|0x40);    //2 MSBs is 01
  /* send argument */
  sd_spi_wr_byte(sd_base, (alt_u8)(argument>>24));
  sd_spi_wr_byte(sd_base, (alt_u8)(argument>>16));
  sd_spi_wr_byte(sd_base, (alt_u8)(argument>>8));
  sd_spi_wr_byte(sd_base, (alt_u8)argument);
  /* send crc; only valid for CMD0 and CMD8 */
  sd_spi_wr_byte(sd_base, crc);
  /* wait for response, up to 8-byte delay */
  for(i=0; i<8; i++){
  /* read R1 response */
  rcode = sd_spi_rd_byte(sd_base);
  if (rcode != 0xff)
    break;
  }
  /* read 4 additional bytes for CMD8 and CMD58 response */
  if (cmd==SD_CMD8_SEND_IF || cmd==SD_CMD58_RD_OCR){
     for(i=0; i<4; i++){
       byte = sd_spi_rd_byte(sd_base);
       ocr = (ocr <<8 | byte);
     }
     // printf("rocde, ocr: 0x%02x, 0x%08x\n", rcode, ocr);
     *r3 = ocr;
  }
  return (rcode);
}

/***********************************************************************
* function: sd_init()
* purpose:  initialize sd card in SPI mode
* argument:
*   sd_base: base address of sd card interface
* return:
*   - status code:
*      - -1: initialization fails
*      -  0: initialization success with standard SD card
*      - +1: initialization success with high capacity SDHC card
* note:
*   - initialize procedure
*      1. send at least 74 sd_clk with sd card deselected (i.e., cs_n=1)
*         to force the sd card to accept native command
*      2. send CMD0 w/ cs asserted (cs_n=0) to force the card
*         to enter SPI mode and reset the card to idle state
*      3. send CMD55 and then CMD41 to initialize the card
*   - different commands needed in step 2 to initialize MMC or SDHC card
*   - initialization may take a fraction of a second
***********************************************************************/
int sd_init(alt_u32 sd_base)
{
  int i;
  alt_u8 rcode;
  alt_u32 ocr;
  int hcs;

  /* set SPI sclk clock to 200 KHz */
  sd_spi_wr_dvsr(sd_base, 125);
  /* force the sd card to enter SPI mode */
  sd_spi_wr_cs(sd_base, 1);          // set cs to 1
  for(i=0; i<10; i++){               // generate 80 sclk cycles
    sd_spi_wr_byte(sd_base, 0xff);   // 8 cycles per write
  }
  sd_spi_wr_cs(sd_base, 0);          // set cs to 0 (enable)
  /* send reset command */
  rcode = sd_wr_cmd(sd_base, SD_CMD0_RESET, 0, &ocr);
  if (rcode != 0x01){                // not entering idle state
     printf("CMD0 command fails: R1=0x%02x \n", rcode);
     return (-1);
  }
  /* send interface condition check command */
  rcode = sd_wr_cmd(sd_base, SD_CMD8_SEND_IF, 0x000001aa, &ocr);
  //printf("Debug CMD8 command: R1/data=0x%02x 0x%x\n", rcode, ocr);
  if ((rcode!=0x01 || ocr!=0x000001aa) && (rcode!=05)) {
    printf("CMD8 command fails: R1/data=0x%02x 0x%x\n", rcode, (int)ocr);
    return (-1);
  }
  /* send sd card init commend and wait for 0.3 sec */
  for(i=0; i<SD_INIT_TIME_OUT; i++){
    sd_wr_cmd(sd_base, SD_CMD55_APP, 0, &ocr);
    rcode = sd_wr_cmd(sd_base, SD_ACMD41_INIT_SD, 0x40000000, &ocr);
    if (rcode==0x00)            // correct response received
      break;
  }
  if (rcode!=0x00){
    printf("ACMD41 command fails: R1=0x%02x\n", rcode);
    return (-1);
  }
  /* send read OCR register commend */
  rcode = sd_wr_cmd(sd_base, SD_CMD58_RD_OCR, 0x000001aa, &ocr);
  // printf("Debug CMD58 command: R1/data=0x%02x 0x%x\n", rcode, (int)ocr);
  if (rcode != 0x00){
     printf("CMD58 command fails: R1=0x%02x \n", rcode);
     return (-1);
  }
  /* extract hcs bit (bit 30) */
  hcs = (ocr & 0x40000000) >> 30;
  /* set SPI clock to 1 MHz */
  sd_spi_wr_dvsr(sd_base, 25);
  return(hcs);
}

/***********************************************************************
* function: sd_read_sector()
* purpose:  retrieve one sector (512 2^9) bytes) from sd card to a buffer
* argument:
*   sd_base: base address of sd card interface
*   sdhc: 0 for SD card; 1 for SDHC card
*   sect: sector number
*   buf: pointer to buffer
* return: 0 for success; -1 otherwise; buf updated
* note:
*   - procedure:
*     1. send read-one-sector command
*     2. wait for sd to send data_start token
*     3. read 512 bytes
*     4. read 2 dummy crc bytes
*   - CMD17 argument
*     - standard capacity SD card: starting byte address (sect<<9)
*     - high capacity SDHC card: starting sector address (sect)
*   - 10 MHz sclk used to calculate # timeout cycles
*   - calling function must allocate 512 byte buffer space
***********************************************************************/
int sd_read_sector(alt_u32 sd_base, int sdhc, alt_u32 sect, alt_u8 *buf)
{
  int i;
  alt_u8 rcode, token;
  alt_u32 addr, ocr;

  /* byte addr for SD card; sector # for SDHC card */
  if (sdhc==0)
    addr = (sect<<9);
  else
    addr = sect;
  /* send sd card read single block commend */
  rcode = sd_wr_cmd(sd_base, SD_CMD17_READ, addr, &ocr);
  if (rcode != 0x00){
    printf("CMD17 command fails: R1=0x%02x \n", rcode);
    return (-1);
  }
  /* wait for data start token up to 0.1 sec */
  for(i=0; i<SD_READ_TIME_OUT; i++){
    token = sd_spi_rd_byte(sd_base);
    if (token==SD_TOKEN_DATA_START)   // correct response received
      break;
  }
  if (token!=SD_TOKEN_DATA_START){   //time-out
    printf("No data start token: last token=0x%02x\n", token);
    return (-1);
  }
  /* read one sector (512 bytes) */
  for (i=0; i<512; i++)
    buf[i] = sd_spi_rd_byte(sd_base);
  /* read and discard two crc bytes */
  sd_spi_rd_byte(sd_base);
  sd_spi_rd_byte(sd_base);
  return (0);
}

/***********************************************************************
* function: sd_write_sector()
* purpose:  write one sector (512 (2^9) bytes) from a buffer to sd card
* argument:
*   sd_base: base address of sd card interface
*   sdhc: 0 for SD card; 1 for SDHC card
*   sect: sector number
*   buf: pointer to buffer
* return: 0 for success; -1 otherwise
* note:
*   - procedure:
*     1. send write-one-sector command
*     2. send data_start token
*     3. send 512 bytes
*     4. send 2 dummy crc bytes
*     5  check data accept token
*     5. wait for completion
*   - CMD24 argument
*     - standard capacity SD card: starting byte address (sect<<9)
*     - high capacity SDHC card: starting sector address (sect)
*   - 10 MHz sclk used to calculate # timeout cycles
***********************************************************************/
int sd_write_sector(alt_u32 sd_base, int sdhc, alt_u32 sect, alt_u8 *buf)
{
  int i;
  alt_u8 rcode, token;
  alt_u32 addr, dummy;

  /* byte addr for SD card; sector # for SDHC card */
  if (sdhc==0)
    addr = (sect<<9);
  else
    addr = sect;
  /* send sd card write single block commend */
  rcode = sd_wr_cmd(sd_base, SD_CMD24_WRITE, addr, &dummy);
  if (rcode != 0x00){         // error
    printf("CMD24 command fails: R1=0x%02x \n", rcode);
    return (-1);
  }
  /* initiate transfer by send data start token */
  sd_spi_wr_byte(sd_base, SD_TOKEN_DATA_START);
  /* send 512 bytes */
  for (i=0; i<512; i++){
    sd_spi_wr_byte(sd_base, buf[i]);
  }
  /* send two dummy crc bytes */
  sd_spi_wr_byte(sd_base, 0xff);
  sd_spi_wr_byte(sd_base, 0xff);
  /* wait for data acceptance token up to 0.25 sec */
  for(i=0; i<SD_WRITE_TIME_OUT; i++){
    token = sd_spi_rd_byte(sd_base);
    token = token & 0x1f;              // only 5 LSBs used
    if (token==SD_TOKEN_DATA_ACCEPT)   // correct response received
      break;
  }
  if (token!=SD_TOKEN_DATA_ACCEPT){
    printf("No data accept token: last token=0x%02x\n", token);
    return (-1);
  }
  /* wait for write completion */
  for(i=0; i<SD_WRITE_TIME_OUT; i++){
    token = sd_spi_rd_byte(sd_base);
    if (token==0xff)                 // correct response received
      break;
  }
  if (token != 0xff){
    printf("Write completion timeout: last token=0x%02x\n", token);
     return (-1);
  }
  return (0);          // ok
}

/***********************************************************************
*  FAT16 related functions
***********************************************************************/
/***********************************************************************
* function: bget16()
* purpose:  get 16 bits from a buffer
* argument:
*   buf: pointer to buffer
*   pos: position in buffer
* return: a half word in alt_u16 data type
* note: "little endian" byte ordering
***********************************************************************/
alt_u16 bget16(alt_u8 *buf, int pos)
{
  alt_u16 b0, b1, r;

  b0 = (alt_u16) buf[pos];
  b1 = (alt_u16) buf[pos+1];
  r = (b1<<8) + b0;
  return(r);
}

/***********************************************************************
* function: bget32()
* purpose:  get 32 bits (a word) from a buffer
* argument:
*   buf: pointer to buffer
*   pos: position in buffer
* return: a word in alt_u32 data type
* note: "little endian" byte ordering
***********************************************************************/
alt_u32 bget32(alt_u8 *buf, int pos)
{
  alt_u32 b0, b1, b2, b3, r;

  b0 = (alt_u32) buf[pos];
  b1 = (alt_u32) buf[pos+1];
  b2 = (alt_u32) buf[pos+2];
  b3 = (alt_u32) buf[pos+3];
  r = (b3<<24) + (b2<<16) + (b1<<8) + b0;
  return(r);
}

/***********************************************************************
* function: sd_file_conv_fname()
* purpose:  convert a string to normalized FAT16 8.3 name-extension entry
* argument:
*   si: pointer to file name string input (e.g., "myfile.c")
*   f83: pointer to 11-char array of normalize 8.3 file name-extension
* return:
*   updated f83
* note:
*   - normalized 8.3 entry:
*       - name: 8 char, padding with \0 if needed
*       - extension: 3 char, padding with \0 if needed
*       - all uppercase
*   - e.g., convert "myfile.c" to "MYFILE  C  "
***********************************************************************/
void sd_file_conv_fname(char *si, char *f83)
{
   int i, pos;
   char ch;

   /* blank */
   for (i=0; i<11; i++)
     f83[i] = ' ';
   /* file name */
   pos=0;
   for (i=0; i<9; i++){
     ch=toupper(si[pos]);
     pos++;
     if (ch=='\0')  // end of string
       return;
     if (ch=='.')
       break;
     f83[i]=ch;
    }
   /* file extension */
   for (i=8; i<11; i++){
     ch=toupper(si[pos]);
     pos++;
     if (ch=='\0')
       return;
     f83[i]=ch;
   }
}

/***********************************************************************
* function: sd_file_mount()
* purpose:  extract key parameters from a FAT16 file system
* argument:
*   sd_base: base address of SD card interface
*   f: pointer to the FAT parameter record
* return:
*   0: successful; f updated
*   1: SD card initialization failed
*   2: SD card read MBR failed
*   3: MBR signature not match
*   4: FAT16 type not match
*   5: SD card read boot record failed
*   6: Boot record signature not match
* note:
*   - file system must be FAT16 and in first partition
*   - procedure
*     1. initialize SD card
*     1. read sector 0
*     2. determine whether the sector is MBR. If not, go to step 6.
*     3. verify MBR signature and FAT file system type
*     4. extract sector number for the first partition's boot record
*     5. read boot record
*     6. verify boot record signature
*     7. extract relevant FAT16 parameters
*     8. construct and return the FAT parameter record
***********************************************************************/
int sd_file_mount(alt_u32 sd_base, fat_para_type *f)
{
  alt_u8 buf[512];   // buffer for a sector
  alt_u32 br0;       // boot record sector number
  alt_u8 sec_per_cls, fat_copy;
  alt_u16 reserved_sec, root_dir_size, sec_per_part_small, sec_per_fat;
  alt_u32 sec_per_part_large;
  int status, sdhc, sec_per_part;

  /* initialize SD card */
  sdhc=sd_init(sd_base);
  if (sdhc==-1){
    printf("SD card initialization failed \n");
    return (1);
  }
  f->sdhc = sdhc;
  f->sd_base = sd_base;
  /* fetch sector 0 */
  status=sd_read_sector(sd_base, sdhc, 0, buf);
  if (status!=0){
    printf("Sector 0 read failed\n");
    return (2);
  }
  br0=0;
  /* check whether the sector is the MBR */
  if (buf[0]!=0xeb && buf[0]!=0xe9) { /* not boot record */
    /* check MBR signature 0x55aa */
    if ((buf[510]!=0x55) || (buf[511]!=0xaa)){
      printf("MBR signature not match\n");
      return (3);
    }
    /* check FAT16 file system type at 0x1c2 */
    if ((buf[0x1c2]!=0x04) && (buf[0x1c2]!=0x06) && (buf[0x1c2]!=0x0e)){
      printf("FAT16 file type not match\n");
      return (4);
    }
    /* fetch boot record of first partition */
    br0 = bget32(buf, 0x1c6);
    status=sd_read_sector(sd_base, sdhc, br0, buf);
    if (status!=0){
      printf("Boot record read failed\n");
      return (5);
    }
  } // end if
  /* check boot record signature 0x55aa */
  if (buf[510]!=0x55 || buf[511]!=0xaa){
    printf("Boot record signature not match\n");
    return (6);
  }
  /* extract key FAT16 parameters */
  sec_per_cls = buf[0x0d];
  reserved_sec = bget16(buf, 0x0e);
  fat_copy = buf[0x10];
  root_dir_size = bget16(buf, 0x11);
  sec_per_part_small = bget16(buf, 0x13);
  sec_per_fat = bget16(buf, 0x16);
  sec_per_part_large = bget32(buf, 0x20);
  /* construct the FAT16 record */
  if (sec_per_part_small!=0)
    sec_per_part = (int) sec_per_part_small;
  else
    sec_per_part = sec_per_part_large;
  f->fat0 = br0 + reserved_sec;
  f->rdir0 = f->fat0 + fat_copy * sec_per_fat;
  f->data0 = f->rdir0 + root_dir_size*32/512;
  f->cls_size = (int) sec_per_cls;
  f->rdir_size = (int) root_dir_size;
  f->data_size = (sec_per_part - f->data0)/sec_per_cls;
  return(0);
}

/***********************************************************************
* function: sd_file_fopen()
* purpose:  open a FAT16 file and store relevant info in file descriptor
* argument:
*   fat: pointer to the FAT parameter record
*   fname: pointer to file name string (such as "myfile.c")
*   fd: pointer to file descriptor
* return:
*   0: successful; fd updated
*   1: file not found
*   2: SD card read data sector failed
*   3: SD card read FAT sector failed
* note:
***********************************************************************/
int sd_file_fopen(fat_para_type *fat, char *fname, file_dp_type *fd)
{
  int index, status, n;
  int sect, oft;
  alt_u8 *buf;   // pointer to a sector buffer
  char f83[11];  // file name in normalized 8.3 format

  sd_file_conv_fname(fname, f83);
  fd->open = 0;
  /* use file descriptor's data buffer as temp buffer */
  buf = fd->dbuf;
  /* search entire root directory */
  for (index=0; index<fat->rdir_size; index++){
    /*  load a new sector after 16 file entries */
    if (index%16==0){
      sect = fat->rdir0 + index/16;
      status=sd_read_sector(fat->sd_base, fat->sdhc, sect, buf);
      if (status!=0){
        printf("SD read failed\n");
        return (2);
      }
    }
    /* offset in current sector */
    oft = 32 * (index%16);
    /* 0x00 in first char of file name means no more entries */
    if (buf[oft]==0x00){
      printf("File not found\n");
      return(1);  // file not found
    }
    /* compare normalized 8.3 name-extension */
    for (n=0; n<11; n++){
      if (f83[n] != buf[oft+n])
        break;
    }
    /* file entry matches; update file descriptor's fields */
    if (n==11){
      fd->rdir_index = index;
      fd->cls0 = bget16(buf, oft+0x1a);
      fd->size = (int) bget32(buf, oft+0x1c);
      for (n=0; n<12; n++)
        fd->name[n] = buf[oft+n];
      /* initialize file descriptor's counters */
      fd->clsi = fd->cls0;
      fd->sect = 0;
      fd->idx = 0;
      fd->seek = 0;
      break;  // success
    } // end if
  } // end for
  if (index==fat->rdir_size){ // file not found
    printf("File not found\n");
    return(1);
  }
  /* load file's 1st file allocation table sector to buffer */
  sect = fat->fat0 + fd->cls0/256;
  status=sd_read_sector(fat->sd_base, fat->sdhc, sect, fd->fbuf);
  if (status!=0){
    printf("File allocation table sector read failed\n");
    return (3);
  }
  fd->sf = sect;
  /* update open status */
  fd->open = 1;
  return(0);
}

/***********************************************************************
* function: sd_file_read_byte()
* purpose:  get 32 bits (a word) from a buffer
* argument:
*   fat: pointer to the FAT parameter record
*   fd: pointer to file descriptor
*   byte: pointer to the returned byte
* return:
*   0: successful; fd updated; byte updated
*   1: end of file
*   2: SD card read data sector failed
*   3: FAT card read FAT sector failed
* note:
*   - file must be opened before read
***********************************************************************/
int sd_file_read_byte(fat_para_type *fat, file_dp_type *fd,alt_u8 *byte)
{
  int status;
  alt_u16 s;

  /* check end-of-file */
  if (fd->seek >= fd->size)
    return(1);
  /* must load a new sector at the beginning */
  if (fd->idx==0){
    s = fat->data0 + ((fd->clsi)-2)*(fat->cls_size) + fd->sect;
    status=sd_read_sector(fat->sd_base, fat->sdhc, s, fd->dbuf);
    if (status!=0){
      printf("Data sector read failed\n");
      return (2);
    }
  }
  /* read a byte */
  *byte = fd->dbuf[fd->idx];
  /* update file descriptor counter */
  fd->seek++;
  fd->idx++;
  /* not reach end of buffer yet */
  if (fd->idx!=512)
    return(0);  // success
  /* reach the end of buffer */
  fd->idx = 0;
  fd->sect++;
  /* not last sector in cluster */
  if (fd->sect!=fat->cls_size)
    return(0);  // success
  /* last sector in cluster; fetch next cluster from FAT table */
  fd->sect = 0;
  s = fat->fat0 + fd->clsi/256;  // sector containing the cluster
  /* file allocation table sector not in buffer; load new sector */
  if (s != fd->sf){
    status=sd_read_sector(fat->sd_base, fat->sdhc, s, fd->fbuf);
    if (status!=0){
      printf("File allocation table sector read failed\n");
      return (3);
    }
    fd->sf = s;
    // printf("Debug: sector %d in FAT\n", s);
  }
  fd->clsi = bget16(fd->fbuf, 2*(fd->clsi%256));
  return(0);  // success
}

/***********************************************************************
* function: sd_file_fclose()
* purpose:  close a FAT16 file
* argument:
*   fd: pointer to file descriptor
* return:
* note: included for completeness
***********************************************************************/
void sd_file_fclose(file_dp_type *fd)
{
  fd->open = 0;
  return;
}


