/***************************************************************************
 * STM32 VGA demo
 * Copyright (C) 2012 Artekit Italy
 * http://www.artekit.eu
 * Written by Ruben H. Meleca
 
### sys.c
 
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


#include "gdi.h"
#include "sys.h"

volatile u32	sysTiming;
volatile u32	sysTicks = 0;
volatile u32	sysDel1Ms;

//*****************************************************************************
//	Function sysInitSystemTimer(void)
//
//	Initialize system timer
//
//
//	return			0=Fail, 1=OK
//*****************************************************************************
u8 sysInitSystemTimer(void) {

	if (SysTick_Config((SystemCoreClock / 1000) -1 )) {
		return(0);
	}
	return(1);
}

//*****************************************************************************
//	Function sysDelay1Ms(void)
//
//	Performs delay 1 milliseconds
//
//	return			None
//*****************************************************************************
void sysDelay1Ms(void) {

	for (sysDel1Ms = 0; sysDel1Ms < 1000; sysDel1Ms++) { };
}


volatile pu16		__timer = (pu16) 0x40006c04;

//*****************************************************************************
//	Function sysDelayMs(u32 dly)
//
//	Performs delay "dly" milliseconds
//
//	parameters		dly		Delay value in milliseconds
//
//	return			None
//*****************************************************************************
void sysDelayMs(u32 dly)
{
	register int32_t				n;
	register int32_t				j;

	for (n=0; n<dly; n++)
	{
		for (j=0; j<20000; j++)  ;		// rough guess, looking for 1 ms delay
	}
}

//*****************************************************************************
//	Function sysDelayMs(u32 dly)
//
//	Performs delay "dly" milliseconds
//
//	parameters		dly		Delay value in milliseconds
//
//	return			None
//*****************************************************************************

void sysTickCount(void) {

	sysTicks++;
	if (sysTiming > 0) --sysTiming;	
}

