/***************************************************************************
 * STM32 VGA demo
 * Copyright (C) 2012 Artekit Italy
 * http://www.artekit.eu
 * Written by Ruben H. Meleca

### video.c

#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

***************************************************************************/

/*
 *  stm32f4_discovery.h is located in Utilities/STM32F4-Discovery
 *  and defines the GPIO Pins where the leds are connected.
 *  Including this header also includes stm32f4xx.h and
 *  stm32f4xx_conf.h, which includes stm32f4xx_gpio.h
 */
#include "stm32f4_discovery.h"

/*
 *  Include all needed standard peripheral driver headers.
 */
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "misc.h"


#include "video.h"



/*
 *  DEBUG
 *  Define macros for accessing the LEDs as a debug tool.
 *
 *  We make code more readable by giving the led-pins
 *  symbolic names depending on the led color.
 *  The values LED4_PIN etc are defined in stm32f4_discovery.h
 *  as GPIO_Pin_12 etc.
 */
#define GREEN			LED4_PIN
#define ORANGE		LED3_PIN
#define RED				LED5_PIN
#define BLUE			LED6_PIN
#define ALL_LEDS		(GREEN | ORANGE | RED | BLUE)		// all leds
#define LEDS_GPIO_PORT (GPIOD)

#define  LED_ON(x)        GPIO_SetBits(LEDS_GPIO_PORT, x)
#define  LED_OFF(x)       GPIO_ResetBits(LEDS_GPIO_PORT, x)



/*
 *  Define the properties of the DMA stream we will use for
 *  the VGA transfers.
 *
 *  The streams and channels available are defined by the
 *  DMA request mapping tables in the STM32F40x docs.  For
 *  SPI1_TX requests, possible choices are:
 *  DMA2, stream 3, channel 3
 *  DMA2, stream 5, channel 3.
 */
#define VIDEO_DMA				 DMA2
#define DMA_STREAM               DMA2_Stream3
#define DMA_CHANNEL              DMA_Channel_3
#define DMA_STREAM_IRQ           DMA2_Stream3_IRQn
#define DMA_IT_TCIF              DMA_IT_TCIF0
#define DMA_STREAM_IRQHANDLER    DMA2_Stream3_IRQHandler


/*
 *  The value for VTOTAL is the number of horizontal bytes to send plus a
 *  a small addition to act as a back porch.  Sending these extra few bytes
 *  via DMA simplifies the code.
 */
#define VTOTAL	(VID_HSIZE+2)			/* Total bytes to send through SPI for one horizontal line */

u8	fb[VID_VSIZE][VTOTAL]  __attribute__((aligned(32)));	/* Frame buffer */

static volatile u16 vline = 0;				/* The current line being drawn */
static volatile u32 vflag = 0;				/* When 1, the SPI DMA request can draw on the screen */
static volatile u32 vdraw = 0;				/* Used to increment vline every 3 drawn lines */

void TIMER_Configuration(void)
{
	GPIO_InitTypeDef			GPIO_InitStructure;
	NVIC_InitTypeDef			nvic;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure = {0,};
	TIM_OCInitTypeDef			TIM_OCInitStructure = {0,};
	u32							TimerPeriod = 0;
	u16							Channel1Pulse = 0;
	u16							Channel2Pulse = 0;
	u16							Channel3Pulse = 0;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PA8 for Alternate Function 2 (TIM1) */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);

	/* Configure PA1 for Alternate Function 2 (TIM2) */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);


	/*
		SVGA 800x600 @ 56 Hz
		Vertical refresh	35.15625 kHz
		Pixel freq.			36.0 MHz

		1 system tick @ 72Mhz = 0,0138 us
	*/

	/*
		Horizontal timing
		-----------------

		Timer 1 period = 35156 Hz

		Timer 1 channel 1 generates a pulse for HSYNC each 28.4 us.
		28.4 us	= Visible area + Front porch + Sync pulse + Back porch.
		HSYNC is 2 us long, so the math to do is:
		2us / 0,0138us = 144 system ticks.

		Timer 1 channel 2 generates a pulse equal to HSYNC + back porch.
		This interrupt will fire the DMA request to draw on the screen if vflag == 1.
		Since firing the DMA takes more or less 800ns, we'll add some extra time.
		The math for HSYNC + back porch is:
		(2us + 3,55us - dma) / 0,0138us = +-350 system ticks

		Horizontal timing info
		----------------------

						Dots	us
		--------------------------------------------
		Visible area	800		22.222222222222
		Front porch		24		0.66666666666667
		Sync pulse		72		2
		Back porch		128		3.5555555555556
		Whole line		1024	28.444444444444

----------------------
Modifications for use with STM32F4 Discovery board.

Timing is based on SystemCoreClock; see system_stm32f4xx.c.

For proper timing, SystemCoreClock must be an even multiple of the pixel frequency!

Timer 1 period = 35156 Hz = SystemCoreClock / 35156
HSYNC period is 2 us (freq = 500 kHz) = SystemCoreClock / 500000
HSYNC + back porch period is 2 us + 3.55 us (freq = 180.0 kHz) = SystemCoreClock / 180000

*/

//	TimerPeriod = 2048;
//	Channel1Pulse = 144;		/* HSYNC */
//	Channel2Pulse = 352; 		/* HSYNC + BACK PORCH */

	TimerPeriod = SystemCoreClock / 35156;			// Ticks per whole line
	Channel1Pulse = SystemCoreClock / 500000;		// HSYNC
	Channel2Pulse = SystemCoreClock / 180000; 		// HSYNC + BACK PORCH

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);		// always init the time base structure first!

	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);		// always init the OC structure first!

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	// PWM2 = clear on compare match
	TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	// was TIM_OCMode_Inactive
	TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);	// added per stm32 tutorial
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);	// added per stm32 tutorial

	TIM_ARRPreloadConfig(TIM1, ENABLE);					// added per STM32 forum

	/* TIM1 counter enable and output enable */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	/* Select TIM1 as Master */
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);

	/*
		Vertical timing
		---------------

		Polarity of vertical sync pulse is positive.

						Lines
		------------------------------
		Visible area	600
		Front porch		1
		Sync pulse		2
		Back porch		22
		Whole frame		625

*/

	/* VSYNC (TIM2_CH2) and VSYNC_BACKPORCH (TIM2_CH3) */
	/* Channel 2 and 3 Configuration in PWM mode */
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Gated);
	TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);

	TimerPeriod = 625;		/* Vertical lines */
	Channel2Pulse = 2;		/* Sync pulse */
	Channel3Pulse = 24;		/* Sync pulse + Back porch */

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		// always init the time base first!

	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);		// always init the OC structure first!

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);


	/*	TIM2 counter enable and output enable */
	TIM_CtrlPWMOutputs(TIM2, ENABLE);

	/* Interrupt TIM2 */
	nvic.NVIC_IRQChannel = TIM2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&nvic);
	TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);

	/* Interrupt TIM1 */
	nvic.NVIC_IRQChannel = TIM1_CC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&nvic);
	TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM1, ENABLE);

//	while (1)  ;			// debug  stop here so we can confirm timer setup
}


/*
 *  For STM32F4 Discovery board, SPI1 MOSI is available on PB5 and
 *  PA7.  Since PA7 is already used for the horizontal timing, edit
 *  the original code to move SPI1 MOSI to PB5.
 */
void SPI_Configuration(void)
{
	NVIC_InitTypeDef		nvic;
	SPI_InitTypeDef			SPI_InitStructure;
	DMA_InitTypeDef			DMA_InitStructure;
	GPIO_InitTypeDef		GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB5 for Alternate Function 5 (SPI1) */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

	SPI_I2S_DeInit(SPI1);
	SPI_Cmd(SPI1, DISABLE);
	DMA_DeInit(DMA_STREAM);


	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32) &fb[0][0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = VTOTAL;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_Channel = DMA_CHANNEL;		// added channel number
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;	// added FIFO mode
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_MemoryBurst_Single;
	DMA_Init(DMA_STREAM, &DMA_InitStructure);

	SPI_StructInit(&SPI_InitStructure);
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	// use 4 for 400 pixels, 2 for 800 pixels
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);

	SPI_CalculateCRC(SPI1, DISABLE);

	nvic.NVIC_IRQChannel = DMA_STREAM_IRQ;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	DMA_STREAM->CR &= ~DMA_SxCR_EN;			// clear the EN bit to disable the stream
	DMA_STREAM->NDTR = VTOTAL;				// set number of bytes to transfer
	DMA_STREAM->M0AR = (u32) &fb[0][0];		// set start of frame buffer

	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);	// allow Tx interrupt to generate DMA requests
	SPI_Cmd(SPI1, ENABLE);

//	while (1)						// debug  send a stream of chars out SPI
//	{
//		SPI1->DR = 0x55;
//		while (SPI1->SR & SPI_FLAG_TXE == RESET)  ;
//	}

	DMA_ITConfig(DMA_STREAM, DMA_IT_TC, ENABLE);
//	VIDEO_DMA->LIFCR = 0x003d0000;			// hard-coded clear of all DMA2 interrupt flags
	DMA_STREAM->CR |= DMA_SxCR_EN;			// set the EN bit to enable the stream
	LED_ON(GREEN);							// debug
}

//*****************************************************************************
//	This irq is generated at the end of the horizontal back porch.
//	Test if inside a valid vertical start frame (vflag variable),
//	and start the DMA to output a single frame buffer line through the SPI device.
//*****************************************************************************
void TIM1_CC_IRQHandler(void)
{
	if (vflag)
	{
//		VIDEO_DMA->LIFCR = 0x003d0000;		// hard-coded clear of all DMA2 interrupt flags
		DMA_STREAM->CR |= DMA_SxCR_EN;		// set the EN bit to enable the stream
//		LED_ON(RED);						// debug
//		LED_OFF(ORANGE);					// debug
	}
	TIM1->SR &= ~TIM_IT_CC2;				// 0xFFFB; //~TIM_IT_CC2;
}

//*****************************************************************************
//	This irq is generated at the end of the vertical back porch.
//	Sets the 'vflag' variable to 1 (valid vertical frame).
//*****************************************************************************
void TIM2_IRQHandler(void)
{
	vflag = 1;
	TIM2->SR &= ~TIM_IT_CC3;				// 0xFFF7; //~TIM_IT_CC3;
}

/*
 *  DMA_STREAM_IRQHANDLER
 *
 *  This code is called when a video stream transfer completes.  This
 *  code disables the stream, then updates values in the stream register
 *  to prepare the stream for the next transfer.
 *
 *  For the STM32F4, you need to use the correct interrupt flag clear
 *  registerr when clearing the transfer complete interrupt flag.
 *  Streams 0 to 3 use DMA_LIFCR, streams 4 to 7 use DMA_HIFCR.
 *
 *  Clear the transfer complete status flag by writing a 1 to it.
 *
 *  Upon exit, the stream is set up but disabled.
 */
void  DMA_STREAM_IRQHANDLER(void)
{
//	VIDEO_DMA->LIFCR = 0x003d0000;			// hard-coded clear of all DMA2 interrupt flags
	VIDEO_DMA->LIFCR = DMA_LIFCR_CTCIF3;	// clear the transfer complete interrupt flag
	DMA_STREAM->CR &= ~DMA_SxCR_EN;			// clear the EN bit to disable the stream
	DMA_STREAM->NDTR = VTOTAL;				// reload the number of bytes to send
//	LED_OFF(RED);							// debug
//	LED_ON(ORANGE);							// debug

	vdraw++;

	if (vdraw == 1)			// was 3
	{
		vdraw = 0;

		vline++;

		if (vline == VID_VSIZE)
		{
			vdraw = vline = vflag = 0;
			DMA_STREAM->M0AR = (u32) &fb[0][0];
		} else {
			DMA_STREAM->M0AR += VTOTAL;
		}
	}
}

void vidClearScreen(void)
{
	u16 x, y;

	for (y = 0; y < VID_VSIZE; y++)
	{
		for (x = 0; x < VTOTAL; x++)
		{
			fb[y][x] = 0;
		}
	}
}

void vidInit(void)
{
/*
 *  Debug
 *
 *  Switch on the PORTD lines that control the LEDs.
 */
	GPIO_InitTypeDef		GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = ALL_LEDS;						// select the pins to modify
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				// set the mode to output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			// set the I/O speed to 100 MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				// set the output type to push-pull
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			// set the pull-up to none
    GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);				// do the init
	LED_ON(BLUE);

	SPI_Configuration();
	TIMER_Configuration();
	vidClearScreen();
}
