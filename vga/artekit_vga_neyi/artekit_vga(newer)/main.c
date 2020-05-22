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

#include "stm32f10x.h"
#include "sys.h"
#include "video.h"
#include "gdi.h"

extern void demoInit(void);
uint32_t a;

void Buzzer_Configuration(uint16_t frequency, uint8_t output) {
	
	TIM_TimeBaseInitTypeDef TIM3_init;
	GPIO_InitTypeDef GPIOA_TIM3_init;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	uint32_t a;
	uint32_t prescaler;
	SystemCoreClockUpdate();
	a = SystemCoreClock;
	prescaler = (a/frequency)/2;
	
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM3_init.TIM_Prescaler = prescaler;
	TIM3_init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM3_init.TIM_Period = 1;
	TIM3_init.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM3, &TIM3_init);
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIOA_TIM3_init.GPIO_Pin = GPIO_Pin_6;
	GPIOA_TIM3_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_TIM3_init.GPIO_Mode = GPIO_Mode_AF_PP;
	
	GPIO_Init(GPIOA, &GPIOA_TIM3_init);
	
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	
	if(output == ENABLE)
	{
      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	}
	else
	{
	    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	}
  TIM_OCInitStructure.TIM_Pulse = 1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
 
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE);
	
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}


void simple_PWM(void){
	TIM_TimeBaseInitTypeDef TIM3_init;
	GPIO_InitTypeDef GPIOA_TIM3_init;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM3_init.TIM_Prescaler = 7200;
	TIM3_init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM3_init.TIM_Period = 100;
	TIM3_init.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM3, &TIM3_init);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIOA_TIM3_init.GPIO_Pin = GPIO_Pin_6;
	GPIOA_TIM3_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_TIM3_init.GPIO_Mode = GPIO_Mode_AF_PP;
	
	GPIO_Init(GPIOA, &GPIOA_TIM3_init);
	
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 50;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
 
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE);
}

int main(void)
{
 	/* TIM1, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_SPI1 | RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //SPI1 glitches
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
  //GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);

	vidInit();
	sysInitSystemTimer();
	
  Buzzer_Configuration(15000,ENABLE);
	//simple_PWM();
	
	sysDelayMs(3000);
	demoInit();
	
	return 0;
}
