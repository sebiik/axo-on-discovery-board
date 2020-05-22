#ifndef __CODEC_WM8731_H
#define __CODEC_WM8731_H

#include "ch.h"
#include "hal.h"

#define WM8731_I2S_ENABLE  rccEnableSPI2(FALSE)
#define WM8731_I2S_DISABLE rccDisableSPI2(FALSE)
#define WM8731_I2C         I2CD2
#define WM8731_I2S         SPI2
#define WM8731_I2SEXT      I2S2ext

#define WM8731_I2C_ADDR       0x1A // 0x1A when CSB pin to ground, else 0x1B
#define WM8731_REG_LLINEIN  	0x00
#define WM8731_REG_RLINEIN  	0x01
#define WM8731_REG_LHEADOUT 	0x02
#define WM8731_REG_RHEADOUT 	0x03
#define WM8731_REG_ANALOG   	0x04
#define WM8731_REG_DIGITAL    0x05
#define WM8731_REG_POWERDOWN  0x06
#define WM8731_REG_INTERFACE	0x07
#define WM8731_REG_SAMPLING 	0x08
#define WM8731_REG_ACTIVE   	0x09
#define WM8731_REG_RESET      0x0F

extern void codec_WM8731_i2s_init_48k(void);
extern bool_t codec_WM8731_hw_reset(void);
extern void codec_WM8731_hw_init(void);
extern bool_t codec_WM8731_writeReg(uint8_t addr, uint16_t data);

#endif /* CODEC_H_ */
