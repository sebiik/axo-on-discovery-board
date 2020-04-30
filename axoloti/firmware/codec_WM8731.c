// #include "codec.h"
#include "codec_WM8731.h"

const stm32_dma_stream_t* i2sdmaWM;
static uint32_t i2stxdmamodeWM = 0;

static const I2CConfig i2cfgWM = {OPMODE_I2C, 100000, STD_DUTY_CYCLE, };

#define I2S2_TX_DMA_CHANNEL STM32_DMA_GETCHANNEL(STM32_SPI_SPI2_TX_DMA_STREAM, STM32_SPI2_TX_DMA_CHN)

static uint8_t txbufWM[2] __attribute__ ((section (".sram2")));
static uint8_t rxbufWM[2] __attribute__ ((section (".sram2")));


void codec_WM8731_hw_init(void) {

	palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); //SCL
	palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); //SDA

	i2cStart(&WM8731_I2C, &i2cfgWM);

	// Reset the codec
	codec_WM8731_hw_reset();

	// Keep codec powered down initially
	codec_WM8731_pwrCtl(0);

	// Slave Mode, I2S Data Format, 32bit, 48k //TODO set to 24bit?
	codec_WM8731_writeReg(WM8731_REG_INTERFACE, 0b00001110);
	// 12.288mhz, 256fs, 48khz in, 48khz out, MCLK/2 //TODO 24mhz?
	codec_WM8731_writeReg(WM8731_REG_SAMPLING,  0b01000000);

	codec_WM8731_pwrCtl(1);

	codec_WM8731_muteCtl(0);
	codec_WM8731_volCtl(0b00010111);
}

void codec_WM8731_hw_reset(void) {
	codec_WM8731_writeReg(WM8731_REG_RESET, 0x00);
	chThdSleepMilliseconds(10);
}

static void dma_i2s_interrupt(void* dat, uint32_t flags) {

  (void)dat;
  (void)flags;

  if ((i2sdmaWM)->stream->CR & STM32_DMA_CR_CT)
    computebufI(rbuf, buf);
  else
    computebufI(rbuf2, buf2);

  dmaStreamClearInterrupt(i2sdmaWM);
}

static void codec_WM8731_dma_init(void) {

	i2sdmaWM = STM32_DMA_STREAM(STM32_SPI_SPI2_TX_DMA_STREAM);

	i2stxdmamodeWM = STM32_DMA_CR_CHSEL(I2S2_TX_DMA_CHANNEL) | STM32_DMA_CR_PL(STM32_SPI_SPI2_DMA_PRIORITY) | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_TEIE | STM32_DMA_CR_TCIE | STM32_DMA_CR_DBM | /* double buffer mode */ STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_WORD;

	dmaStreamAllocate(i2sdmaWM, STM32_SPI_SPI2_IRQ_PRIORITY, (stm32_dmaisr_t)dma_i2s_interrupt, (void *)&SPID2);

	dmaStreamSetPeripheral(i2sdmaWM, &(WM8731_I2S->DR));
	dmaStreamSetMemory0(i2sdmaWM, buf);
	dmaStreamSetMemory1(i2sdmaWM, buf2);
	dmaStreamSetTransactionSize(i2sdmaWM, 64);
	dmaStreamSetMode(i2sdmaWM, i2stxdmamodeWM | STM32_DMA_CR_MINC);

	//TODO: add RX

	dmaStreamClearInterrupt(i2sdmaWM);
	dmaStreamEnable(i2sdmaWM);
}

void codec_WM8731_i2s_init_48k(void) {

	//TODO: | PAL_STM32_OSPEED_HIGHEST?
	//TODO: palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5)); //WS

	// palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5)); //BCK

	palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5)); //ext_SD maybe AF6?

	// palSetPadMode(GPIOB, 15, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5)); //SD

	// palSetPadMode(GPIOC, 6, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 6,  PAL_MODE_ALTERNATE(5)); //MCLK

// SPI2 in I2S Mode, Master
	WM8731_I2S_ENABLE;
	WM8731_I2S->I2SCFGR = SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_I2SCFG_1
			| SPI_I2SCFGR_DATLEN_1;
	WM8731_I2S->I2SPR = SPI_I2SPR_MCKOE | SPI_I2SPR_ODD | 3;
	codec_WM8731_dma_init();
	WM8731_I2S->CR2 = SPI_CR2_TXDMAEN;
	WM8731_I2S->I2SCFGR |= SPI_I2SCFGR_I2SE;
}

void codec_WM8731_writeReg(uint8_t addr, uint8_t data) {

	txbufWM[0] = (addr << 1) | ((data >> 8) & 1);
	txbufWM[1] = data & 0xFF;
	
	i2cMasterTransmitTimeout(&WM8731_I2C, WM8731_I2C_ADDR, txbufWM, 2, NULL, 0, MS2ST(4));
  chThdSleepMilliseconds(1);
}

void codec_WM8731_pwrCtl(uint8_t pwr) {

	if (pwr)
		codec_WM8731_writeReg(WM8731_REG_POWERDOWN, 0x00);
	else
		codec_WM8731_writeReg(WM8731_REG_POWERDOWN, 0x01);
}

void codec_WM8731_muteCtl(uint8_t mute) {

	if (mute)
		codec_WM8731_writeReg(WM8731_REG_DIGITAL, 0x08);
	else {
		codec_WM8731_writeReg(WM8731_REG_DIGITAL, 0x00);
		codec_WM8731_writeReg(WM8731_REG_ANALOG, 0x10);    // DAC selected
	}
}

void codec_WM8731_volCtl(uint8_t vol) {

	if (vol <= 0x1F) {
		codec_WM8731_writeReg(WM8731_REG_LLINEIN, vol & 0x1F);
		codec_WM8731_writeReg(WM8731_REG_RLINEIN, vol & 0x1F);
	}
	else {
		codec_WM8731_writeReg(WM8731_REG_LLINEIN, 0x1F);
		codec_WM8731_writeReg(WM8731_REG_RLINEIN, 0x1F);
	}
}