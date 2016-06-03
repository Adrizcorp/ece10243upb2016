/***********************************************************************
*
* Module:  Audio codec driver header
* File:    chu_avalon_audio.h
* Purpose: Routines to configure codec, retrieve data from ADC, and
*          send data to DAC
*
************************************************************************
*  Register map
************************************************************************
* Read (data to cpu):
*   offset 1
*     * bit 0: i2c idle
*     * bit 1: dac fifo full
*     * bit 2: adc fifo empty
*   offset 3
*     * bits 31 to 0: stereo audio data (16-bit left + 16-bit right)
* Write (data from cpu):
*   offset 0
*     * bits 23-0: 24-bit codec command to i2c bus
*   offset 1
*     * bit 0: dac data stream select
*     * bit 1: adc data stream select
*   offset 2
*     * bits 31 to 0: stereo audio data (16-bit left + 16-bit right)
***********************************************************************/
/* file inclusion */
#include <alt_types.h>

/***********************************************************************
* constant definitions
***********************************************************************/
#define CHU_AUD_I2C_DATA_REG     0
#define CHU_AUD_STATUS_REG       1
#define CHU_AUD_DBUS_SEL_REG     1
#define CHU_AUD_DAC_DATA_REG     2
#define CHU_AUD_ADC_DATA_REG     3

/***********************************************************************
* Function prototypes
***********************************************************************/
/* I2C functions */
int audio_i2c_is_idle(alt_u32 audio_base);
void audio_i2c_wr_cmd(alt_u32 audio_base, alt_u8 addr, alt_u16 cmd);
void audio_init(alt_u32 audio_base);

/* data routing selection */
void audio_wr_src_sel(alt_u32 audio_base, int dac_sel, int adc_sel);

/* dac functions */
int audio_dac_fifo_full(alt_u32 audio_base);
void audio_dac_wr_fifo(alt_u32 audio_base, alt_u32 data);

/* adc functions */
int audio_adc_fifo_empty(alt_u32 audio_base);
alt_u32 audio_adc_rd_fifo(alt_u32 audio_base);
