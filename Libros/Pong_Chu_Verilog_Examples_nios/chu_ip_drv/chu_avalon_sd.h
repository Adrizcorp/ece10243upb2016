/***********************************************************************
*
* Module:  SPI, SD card and FAT16 driver header
* File:    chu_avalon_sd.h
* Purpose: Routines to initialize and read/write SD card and
*          to read a file from FAT16 file system
*
************************************************************************
*  Register map
************************************************************************
* Read (data to cpu):
*   offset 0
*     * bit 7-0: 8-bit read data
*     *  bit 8: SPI controller idle bit
* Write (data from cpu):
*   offset 1
*     * bit:0 chip select (ss)
*   offset 2
*     * bits 7 to 0: sclk clock divisor
*   offset 3
*     * bits 7 to 0: 8-bit write data
*
***********************************************************************/
/* file inclusion */
#include <alt_types.h>

/***********************************************************************
* data type definitions
***********************************************************************/
/* data type for FAT parameters */
/* the basic unit is sector in general */
typedef struct tag_fat
{
  alt_32 sd_base;     // base address of SD card interface
  int sdhc;           // type of SD card
  alt_u16 rdir0;      // starting sector of root directory
  alt_u16 fat0;       // starting sector of FAT table
  alt_u16 data0;      // starting sector of data region
  int cls_size;       // # sectors per cluster
  int rdir_size;      // max # file entries in root directory
  int data_size;      // max # clusters for data
} fat_para_type;

/* data type for file parameters */
typedef struct tag_file_descriptor
{
  char name[11];       // 11-bit file name+extension
  int rdir_index;      // entry index in root directory table
  int size;            // size of file in byte
  alt_u16 cls0;        // starting cluster number
  alt_u16 clsi;        // current data cluster number
  int sect;            // current sector
  int idx;             // current index in sector
  int seek;            // current position in file
  char dbuf[512];      // data sector buffer
  int sf;              // current fat sector number
  char fbuf[512];      // fat sector buffer
  int open;            // file is properly opened
} file_dp_type;

/***********************************************************************
* constant definitions
***********************************************************************/
/* SPI registers */
#define CHU_SD_RD_DATA_REG     0
#define CHU_SD_CS_REG          1
#define CHU_SD_DVSR_REG        2
#define CHU_SD_WR_DATA_REG     3

/* SD card commands */
#define SD_CMD0_RESET          0
#define SD_CMD1_INIT_MMC       1    // not used for SD
#define SD_CMD8_SEND_IF        8
#define SD_CMD17_READ         17
#define SD_CMD24_WRITE        24
#define SD_CMD55_APP          55
#define SD_CMD58_RD_OCR       58
#define SD_ACMD41_INIT_SD     41
/* SD card token */
#define SD_TOKEN_DATA_START   0xfe
#define SD_TOKEN_DATA_ACCEPT  0x05
/* SD card timeout cycles */
#define SD_INIT_TIME_OUT      900     // 0.50s w/ 200 KHz sclk
#define SD_READ_TIME_OUT      312500  // 0.10s w/ 25 MHz sclk
#define SD_WRITE_TIME_OUT     781250  // 0.25s w/ 25 MHz sclk


/***********************************************************************
* Function prototypes
***********************************************************************/
/* SPI functions */
int sd_spi_is_ready(alt_u32 sd_base);
void sd_spi_wr_cs(alt_u32 sd_base, int en_bit);
void sd_spi_wr_dvsr(alt_u32 sd_base, alt_u8 dvsr);
void sd_spi_wr_byte(alt_u32 sd_base, alt_u8 spi_data);
alt_u8 sd_spi_rd_byte(alt_u32 sd_base);

/* SD card functions */
alt_u8 sd_wr_cmd(alt_u32 sd_base, alt_u8 cmd, alt_u32 argument, alt_u32 *r3);
int sd_init(alt_u32 sd_base);
int sd_read_sector(alt_u32 sd_base, int sdhc, alt_u32 sect, alt_u8 *buf);
int sd_write_sector(alt_u32 sd_base, int sdhc, alt_u32 sect, alt_u8 *buf);

/* FAT16 functions */
int sd_file_mount(alt_u32 sd_base, fat_para_type *f);
int sd_file_fopen(fat_para_type *fat, char *fname, file_dp_type *fd);
void sd_file_conv_fname(char *si, char *so);
int sd_file_read_byte(fat_para_type *fat, file_dp_type *fd, alt_u8 *byte);
void sd_file_fclose(file_dp_type *fd);
