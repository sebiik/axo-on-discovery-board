#include "codec_WM8731.h"
#include "axoloti_board.h"
// #include "exceptions.h"

const stm32_dma_stream_t* i2s_dma_tx;
const stm32_dma_stream_t* i2s_dma_rx;

static const I2CConfig i2cfgWM = {OPMODE_I2C, 100000, STD_DUTY_CYCLE, };

#define I2S2_TX_DMA_CHANNEL STM32_DMA_GETCHANNEL(STM32_SPI_SPI2_TX_DMA_STREAM, STM32_SPI2_TX_DMA_CHN)

#define I2S2EXT_RX_DMA_CHANNEL STM32_DMA_GETCHANNEL(STM32_SPI_SPI2_RX_DMA_STREAM, 3)

#define I2S2ext_RX_DMA_CHANNEL \
STM32_DMA_GETCHANNEL(STM32_DMA_STREAM_ID(1, 3), \
3)

static uint8_t i2c_txbuf[2] __attribute__ ((section (".sram2")));


bool_t codec_WM8731_hw_reset(void) {

	palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(4) | PAL_STM32_PUDR_PULLUP | PAL_STM32_OTYPE_OPENDRAIN); //SCL
	palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(4) | PAL_STM32_PUDR_PULLUP | PAL_STM32_OTYPE_OPENDRAIN); //SDA

	// chMtxLock(&Mutex_DMAStream_1_7);

	i2cStart(&WM8731_I2C, &i2cfgWM);
	i2cAcquireBus(&WM8731_I2C);

	msg_t status;
	status = codec_WM8731_writeReg(WM8731_REG_RESET, 0x00);
	i2cReleaseBus(&WM8731_I2C);
	i2cStop(&WM8731_I2C);
	if (status == RDY_OK) return true;
	else return false;
}


void codec_WM8731_hw_init(void) {

	palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(4) | PAL_STM32_PUDR_PULLUP | PAL_STM32_OTYPE_OPENDRAIN); //SCL
	palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(4) | PAL_STM32_PUDR_PULLUP | PAL_STM32_OTYPE_OPENDRAIN); //SDA

	// chMtxLock(&Mutex_DMAStream_1_7);

	i2cStart(&WM8731_I2C, &i2cfgWM);
	i2cAcquireBus(&WM8731_I2C);

	/*
	STARTUP SEQUENCE FROM THE WM8731 DATASHEET:
	- Switch on power supplies. By default the WM8731 is in Standby Mode, the DAC is digitally muted and the Audio Interface and Outputs are all OFF.
	- Set all required bits in the Power Down register (0x06) to ‘0’; EXCEPT the OUTPD bit, this should be set to ‘1’ (Default).
	- Set required values in all other registers except 0x09 (Active).
	- Set the ‘Active’ bit in register 0x09.
	- The last write of the sequence should be setting OUTPD to ‘0’ (active) in register 0x06, enabling the DAC signal path, free of any significant power-up noise.
	*/

	// Reg 06: Power Down Control (Clkout, Osc, OUTPD, Mic bits set) 0111 0010
	codec_WM8731_writeReg(WM8731_REG_POWERDOWN, 0x72);

	// Reg 00: Left Line In (0dB, mute off) 0001 0111
	codec_WM8731_writeReg(WM8731_REG_LLINEIN,0x17);

	// Reg 01: Right Line In (0dB, mute off) 0001 0111
	codec_WM8731_writeReg(WM8731_REG_RLINEIN,0x17);

	// Reg 02: Left Headphone out (0dB) 0111 1001 //TODO can mute?
	codec_WM8731_writeReg(WM8731_REG_LHEADOUT,0x79);

	// Reg 03: Right Headphone out (0dB) 0111 1001
	codec_WM8731_writeReg(WM8731_REG_RHEADOUT,0x79);

	// Reg 04: Analog Audio Path Control (DAC sel, Mute Mic) 0001 0010
	codec_WM8731_writeReg(WM8731_REG_ANALOG,0x12);

	// Reg 05: Digital Audio Path Control
	codec_WM8731_writeReg(WM8731_REG_DIGITAL,0x00);

	// Reg 07: Digital Audio Interface Format (i2s, 24-bit, slave) 0000 1010
	codec_WM8731_writeReg(WM8731_REG_INTERFACE,0x0A);

	// Reg 08: Sampling Control (Normal, 256x, 48k ADC/DAC, MCLK/2) 0100 0000
	codec_WM8731_writeReg(WM8731_REG_SAMPLING,0x40);
	chThdSleepMilliseconds(5);

	// Reg 09: Set ACTIVE
	codec_WM8731_writeReg(WM8731_REG_ACTIVE, 0x01);
	chThdSleepMilliseconds(5);

	// Reg 06: Power Down Control (Clkout, Osc, Mic bits set) 0110 0010
	codec_WM8731_writeReg(WM8731_REG_POWERDOWN, 0x62);
	i2cReleaseBus(&WM8731_I2C);
	i2cStop(&WM8731_I2C);

	// chMtxUnlock();
}


static void dma_i2s_interrupt(void* dat, uint32_t flags) {

	(void)dat;
	(void)flags;

	if ((i2s_dma_tx)->stream->CR & STM32_DMA_CR_CT) {
		computebufI(rbuf, buf);
	}
	else {
		computebufI(rbuf2, buf2);
	}

	dmaStreamClearInterrupt(i2s_dma_tx);
}


static void dma_i2s_rx_interrupt(void* dat, uint32_t flags) {

	(void)dat;
	(void)flags;

	dmaStreamClearInterrupt(i2s_dma_rx);
}


static void codec_WM8731_dma_init(void) {

	// TX
	i2s_dma_tx = STM32_DMA_STREAM(STM32_SPI_SPI2_TX_DMA_STREAM);

	uint32_t i2s_dma_tx_mode = STM32_DMA_CR_CHSEL(I2S2_TX_DMA_CHANNEL) | STM32_DMA_CR_PL(STM32_SPI_SPI2_DMA_PRIORITY) | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_TEIE | STM32_DMA_CR_TCIE | STM32_DMA_CR_DBM | STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_WORD;

	dmaStreamAllocate(i2s_dma_tx, STM32_SPI_SPI2_IRQ_PRIORITY, (stm32_dmaisr_t)dma_i2s_interrupt, (void *)&SPID2);

	dmaStreamSetPeripheral(i2s_dma_tx, &(WM8731_I2S->DR));
	dmaStreamSetMemory0(i2s_dma_tx, buf);
	dmaStreamSetMemory1(i2s_dma_tx, buf2);
	dmaStreamSetTransactionSize(i2s_dma_tx, 64);
	dmaStreamSetMode(i2s_dma_tx, i2s_dma_tx_mode | STM32_DMA_CR_MINC);

	// RX
	i2s_dma_rx = STM32_DMA_STREAM(STM32_SPI_SPI2_RX_DMA_STREAM);

	uint32_t i2s_dma_rx_mode = STM32_DMA_CR_CHSEL(3 /*I2S2_RX_DMA_CHANNEL*/) | STM32_DMA_CR_PL(STM32_SPI_SPI2_DMA_PRIORITY) | STM32_DMA_CR_DIR_P2M | STM32_DMA_CR_TEIE | STM32_DMA_CR_TCIE | STM32_DMA_CR_DBM | STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_WORD;

	dmaStreamAllocate(i2s_dma_rx, STM32_SPI_SPI2_IRQ_PRIORITY, (stm32_dmaisr_t)dma_i2s_rx_interrupt, (void *)&SPID2);

	dmaStreamSetPeripheral(i2s_dma_rx, &(WM8731_I2SEXT->DR));
	dmaStreamSetMemory0(i2s_dma_rx, rbuf);
	dmaStreamSetMemory1(i2s_dma_rx, rbuf2);
	dmaStreamSetTransactionSize(i2s_dma_rx, 64);
	dmaStreamSetMode(i2s_dma_rx, i2s_dma_rx_mode | STM32_DMA_CR_MINC);

	// enable RX
	dmaStreamClearInterrupt(i2s_dma_rx);
	dmaStreamEnable(i2s_dma_rx);

	// enable TX
	dmaStreamClearInterrupt(i2s_dma_tx);
	dmaStreamEnable(i2s_dma_tx);
}


void codec_WM8731_i2s_init_48k(void) {

	palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 15, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC,  6, PAL_MODE_OUTPUT_PUSHPULL);

	palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5)); // WS
	palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5)); // BCK
	palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5)); // ext_SD
	palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5)); // SD
	palSetPadMode(GPIOC,  6, PAL_MODE_ALTERNATE(5)); // MCLK

	// SPI2 in I2S Mode, Master
	WM8731_I2S_ENABLE;

	WM8731_I2S->I2SCFGR     = SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_I2SCFG_1 | SPI_I2SCFGR_DATLEN_1; /* MASTER TRANSMIT */
	WM8731_I2S->I2SPR       = SPI_I2SPR_MCKOE | SPI_I2SPR_ODD | 3;

	WM8731_I2SEXT->I2SCFGR  = SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_I2SCFG_0 | SPI_I2SCFGR_DATLEN_1; /* SLAVE RECEIVE*/
	WM8731_I2SEXT->I2SPR    = SPI_I2SPR_ODD | 3;

	codec_WM8731_dma_init();

	WM8731_I2S->CR2         = SPI_CR2_TXDMAEN;
	WM8731_I2SEXT->CR2      = SPI_CR2_RXDMAEN;

	WM8731_I2S->I2SCFGR    |= SPI_I2SCFGR_I2SE;
	WM8731_I2SEXT->I2SCFGR |= SPI_I2SCFGR_I2SE;

}


bool_t codec_WM8731_writeReg(uint8_t addr, uint16_t data) {

	i2c_txbuf[0] = (addr << 1) | ((data >> 8) & 1);
	i2c_txbuf[1] = data & 0xFF;
	msg_t status = -1;
	uint8_t attempt = 0;
	systime_t tmo = MS2ST(4);

	// Attempt to transmit up to 30 times,
	while (attempt < 30) {
		++attempt;
		status = i2cMasterTransmitTimeout(&WM8731_I2C, WM8731_I2C_ADDR, i2c_txbuf, 2, NULL, 0, tmo);
		if (status == RDY_OK) return true;
		chThdSleepMilliseconds(1);
	}
	// Return false if unsuccessful after tries, set orange LED and report exception.
	palSetPad(LED3_PORT, LED3_PIN);
	report_wm8731_codec_i2c_error();
	return false;
}


void codec_WM8731_I2SStop(void) {

	WM8731_I2S->I2SCFGR    = 0;
	WM8731_I2SEXT->I2SCFGR = 0;
	WM8731_I2S->CR2        = 0;
	WM8731_I2SEXT->CR2     = 0;
}
