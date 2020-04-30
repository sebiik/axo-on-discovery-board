// #include "codec.h"
#include "codec_WM8731.h"

const stm32_dma_stream_t* i2s_dma_tx;

static const I2CConfig i2cfgWM = {OPMODE_I2C, 100000, STD_DUTY_CYCLE, };

#define I2S2_TX_DMA_CHANNEL STM32_DMA_GETCHANNEL(STM32_SPI_SPI2_TX_DMA_STREAM, STM32_SPI2_TX_DMA_CHN)

static uint8_t txbufWM[2] __attribute__ ((section (".sram2")));
// static uint8_t rxbufWM[2] __attribute__ ((section (".sram2")));

// extern void dma_i2s_interrupt(void *, uint32_t);

void codec_WM8731_hw_init(void) {

	palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); //SCL
	palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); //SDA

	i2cStart(&WM8731_I2C, &i2cfgWM);

	codec_WM8731_hw_reset();

	// Slave Mode, I2S Data Format, 32bit, 48k //TODO: maybe input works with 32bit?
	// codec_WM8731_writeReg(WM8731_REG_INTERFACE, 0b000001110);

	// Slave Mode, I2S Data Format, 24bit, 48k
	codec_WM8731_writeReg(WM8731_REG_INTERFACE, 0b000001010);


	// 256fs, 48khz in, 48khz out, MCLK/2
	codec_WM8731_writeReg(WM8731_REG_SAMPLING,  0b001000000);

	// 256fs, 48khz in, 48khz out, MCLK
	// codec_WM8731_writeReg(WM8731_REG_SAMPLING,  0b000000000);


	// Keep codec powered down initially
	codec_WM8731_pwrCtl(0);
	codec_WM8731_muteCtl(0);

	codec_WM8731_activeCtl(1);

	chThdSleepMilliseconds(5);

	codec_WM8731_pwrCtl(1);

	codec_WM8731_lineInVolCtl(0b00010111);
	codec_WM8731_headphoneVolCtl(0b001111001);
}

void codec_WM8731_hw_reset(void) {
	codec_WM8731_writeReg(WM8731_REG_RESET, 0x00);
	chThdSleepMilliseconds(1);
}

static void dma_i2s_interrupt(void* dat, uint32_t flags) {

  (void)dat;
  (void)flags;

  if ((i2s_dma_tx)->stream->CR & STM32_DMA_CR_CT)
    computebufI(rbuf, buf);
  else
    computebufI(rbuf2, buf2);

  dmaStreamClearInterrupt(i2s_dma_tx);
}

static void codec_WM8731_dma_init(void) {

	i2s_dma_tx = STM32_DMA_STREAM(STM32_SPI_SPI2_TX_DMA_STREAM);

	uint32_t i2s_dma_tx_mode = STM32_DMA_CR_CHSEL(I2S2_TX_DMA_CHANNEL) | STM32_DMA_CR_PL(STM32_SPI_SPI2_DMA_PRIORITY) | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_TEIE | STM32_DMA_CR_TCIE | STM32_DMA_CR_DBM | /* double buffer mode */ STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_WORD;

	dmaStreamAllocate(i2s_dma_tx, STM32_SPI_SPI2_IRQ_PRIORITY, (stm32_dmaisr_t)dma_i2s_interrupt, (void *)&SPID2);

	dmaStreamSetPeripheral(i2s_dma_tx, &(WM8731_I2S->DR));
	dmaStreamSetMemory0(i2s_dma_tx, buf);
	dmaStreamSetMemory1(i2s_dma_tx, buf2);
	dmaStreamSetTransactionSize(i2s_dma_tx, 64);
	dmaStreamSetMode(i2s_dma_tx, i2s_dma_tx_mode | STM32_DMA_CR_MINC);

	//TODO: add RX

	dmaStreamClearInterrupt(i2s_dma_tx);
	dmaStreamEnable(i2s_dma_tx);
}

void codec_WM8731_i2s_init_48k(void) {

	//TODO: | PAL_STM32_OSPEED_HIGHEST?
	// ..._PUSHPULL is what fixed it!
	palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5)); //WS

	palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5)); //BCK

	// palSetPadMode(GPIOB, 14, PAL_MODE_INPUT); //TODO try this
	palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5)); //ext_SD maybe AF6?

	palSetPadMode(GPIOB, 15, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5)); //SD

	palSetPadMode(GPIOC, 6, PAL_MODE_OUTPUT_PUSHPULL);
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

void codec_WM8731_writeReg(uint8_t addr, uint16_t data) {

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

	if (mute) {
		codec_WM8731_writeReg(WM8731_REG_DIGITAL, 0x08);
  }
	else {
		codec_WM8731_writeReg(WM8731_REG_DIGITAL, 0x00);
		codec_WM8731_writeReg(WM8731_REG_ANALOG, 0x12);    // DAC selected, mute mic
	}
}

void codec_WM8731_lineInVolCtl(uint8_t vol) {

	if (vol <= 0x1F) {
		codec_WM8731_writeReg(WM8731_REG_LLINEIN, vol & 0x1F);
		codec_WM8731_writeReg(WM8731_REG_RLINEIN, vol & 0x1F);
	}
	else {
		codec_WM8731_writeReg(WM8731_REG_LLINEIN, 0x1F);
		codec_WM8731_writeReg(WM8731_REG_RLINEIN, 0x1F);
	}
}

void codec_WM8731_headphoneVolCtl(uint16_t vol) {

	if (vol <= 0x7F) {
		codec_WM8731_writeReg(WM8731_REG_LHEADOUT, vol & 0x7F);
		codec_WM8731_writeReg(WM8731_REG_RHEADOUT, vol & 0x7F);
	}
	else {
		codec_WM8731_writeReg(WM8731_REG_LHEADOUT, 0x7F);
		codec_WM8731_writeReg(WM8731_REG_RHEADOUT, 0x7F);
	}
}

void codec_WM8731_activeCtl(uint8_t active) {

	if (active)
		codec_WM8731_writeReg(WM8731_REG_ACTIVE, 0x01);
	else
		codec_WM8731_writeReg(WM8731_REG_ACTIVE, 0x00);
}
