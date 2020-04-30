#ifndef __CODEC_WM8731_H
#define __CODEC_WM8731_H

#include "ch.h"
#include "hal.h"

#define WM8731_I2C I2CD2
#define WM8731_I2S_ENABLE rccEnableSPI2(FALSE)
#define WM8731_I2S_DISABLE rccDisableSPI2(FALSE)
#define WM8731_I2S SPI2
#define WM8731_I2Sext I2S2ext

#define WM8731_I2C_ADDR 0x1A // address when CSB pin to ground, else 0x1B
#define WM8731_REG_LLINEIN  	0 // 0b 000 0000
#define WM8731_REG_RLINEIN  	1 // 0b 000 0001
#define WM8731_REG_LHEADOUT 	2 // 0b 000 0010
#define WM8731_REG_RHEADOUT 	3 // 0b 000 0011
#define WM8731_REG_ANALOG   	4 // 0b 000 0100
#define WM8731_REG_DIGITAL	  5 // 0b 000 0101
#define WM8731_REG_POWERDOWN  6 // 0b 000 0110
#define WM8731_REG_INTERFACE	7 // 0b 000 0111
#define WM8731_REG_SAMPLING 	8 // 0b 000 1000
#define WM8731_REG_ACTIVE   	9 // 0b 000 1001
#define WM8731_REG_RESET     15 // 0b 000 1111

extern void codec_WM8731_hw_init(void);
extern void codec_WM8731_hw_reset(void);
extern void codec_WM8731_writeReg(uint8_t addr, uint8_t data);
extern void codec_WM8731_volCtl(uint8_t vol);
extern void codec_WM8731_pwrCtl(uint8_t pwr);
extern void codec_WM8731_muteCtl(uint8_t mute);
extern void codec_WM8731_i2s_init_48k(void);
extern void codec_WM8721_I2CStop(void);

#endif /* CODEC_H_ */
