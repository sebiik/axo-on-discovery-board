/**
 * Copyright (C) 2013, 2014 Johannes Taelman
 * Copyright (C) 2016, Ricard Wanderlof
 *
 * This file is part of Axoloti.
 * Axoloti is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Axoloti is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Axoloti. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Adapted from codec_CS43L22.c
 * Created on: Jun 7, 2012
 * Author: Kumar Abhishek
 */

#include "codec.h"
#include "codec_CS4354.h"

const stm32_dma_stream_t* i2sdma;
static uint32_t i2stxdmamode = 0;



#define I2S3_TX_DMA_CHANNEL \
STM32_DMA_GETCHANNEL(STM32_SPI_SPI3_TX_DMA_STREAM, \
STM32_SPI3_TX_DMA_CHN)

static void dma_i2s_interrupt(void* dat, uint32_t flags) {
  (void)dat;
  (void)flags;

  if ((i2sdma)->stream->CR & STM32_DMA_CR_CT) {
    computebufI(rbuf, buf);
  }
  else {
    computebufI(rbuf2, buf2);
  }
  dmaStreamClearInterrupt(i2sdma);
}

static void codec_CS4354_dma_init(void) {
  i2sdma = STM32_DMA_STREAM(STM32_SPI_SPI3_TX_DMA_STREAM);

  i2stxdmamode = STM32_DMA_CR_CHSEL(I2S3_TX_DMA_CHANNEL)
      | STM32_DMA_CR_PL(STM32_SPI_SPI3_DMA_PRIORITY) | STM32_DMA_CR_DIR_M2P
      | STM32_DMA_CR_TEIE | STM32_DMA_CR_TCIE | STM32_DMA_CR_DBM | // double buffer mode
      STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_WORD;

  dmaStreamAllocate(i2sdma, STM32_SPI_SPI3_IRQ_PRIORITY,
                    (stm32_dmaisr_t)dma_i2s_interrupt, (void *)&SPID3);

  dmaStreamSetPeripheral(i2sdma, &(SPI3->DR));
  dmaStreamSetMemory0(i2sdma, buf);
  dmaStreamSetMemory1(i2sdma, buf2);
  dmaStreamSetTransactionSize(i2sdma, 64);
  dmaStreamSetMode(i2sdma, i2stxdmamode | STM32_DMA_CR_MINC);
  dmaStreamClearInterrupt(i2sdma);
  dmaStreamEnable(i2sdma);
}

void codec_CS4354_i2s_init_48k(void) {
  palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOA, 4, PAL_MODE_ALTERNATE(6)); /* WS */
  palSetPadMode(GPIOB, 3, PAL_MODE_ALTERNATE(6)); /* CLK */
  palSetPadMode(GPIOC, 12, PAL_MODE_ALTERNATE(6)); /* SD */
  palSetPadMode(GPIOC, 7, PAL_MODE_ALTERNATE(6)); /* MCLK */

// SPI3 in I2S Mode, Master, MCLK=256*fs
  CODEC_I2S_ENABLE;
  CODEC_I2S->I2SCFGR = SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_I2SCFG_1
      | SPI_I2SCFGR_DATLEN_1;
  CODEC_I2S->I2SPR = SPI_I2SPR_MCKOE | SPI_I2SPR_ODD | 3;
  codec_CS4354_dma_init();
  CODEC_I2S->CR2 = SPI_CR2_TXDMAEN;
  CODEC_I2S->I2SCFGR |= SPI_I2SCFGR_I2SE;
}
