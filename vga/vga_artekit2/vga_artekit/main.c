/***************************************************************************
 * STM32 VGA demo
 * Copyright (C) 2012 Artekit Italy
 * http://www.artekit.eu
 * Written by Ruben H. Meleca
 
### main.c
 
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
#include "misc.h"


#include "sys.h"
#include "video.h"
#include "gdi.h"



/*
 *  Define a structure for inializing the LED port lines.
 */

extern void demoInit(void);

void RCC_Configuration(void)
{
	/* TIM1, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
	/* Original code initialized AFI0; what is it?  */

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA |
			RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_TIM1 |
			RCC_APB2Periph_SPI1, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// debug only for LEDs
}

void GPIO_Configuration(void)
{
}



int main(void)
{
	SystemInit();
	RCC_Configuration();
	GPIO_Configuration();

	vidInit();
//	sysInitSystemTimer();
	
	demoInit();
	
	return 0;
}
