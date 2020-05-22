/***************************************************************************
 * STM32 VGA demo
 * Copyright (C) 2012 Artekit Italy
 * http://www.artekit.eu
 * Written by Ruben H. Meleca
 
### demo.c
 
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

 *
 *  Modified 31 Dec 2014  Karl Lunt
 *  Ported to the STM32F4 Discovery board.
 *

***************************************************************************/

/*
 *  stm32f4_discovery.h is located in Utilities/STM32F4-Discovery
 *  and defines the GPIO Pins where the leds are connected.
 *  Including this header also includes stm32f4xx.h and
 *  stm32f4xx_conf.h, which includes stm32f4xx_gpio.h
 */
#include "stm32f4_discovery.h"

#include "sys.h"
#include "video.h"
#include "gdi.h"
#include "string.h"
#include <stdlib.h>

// extern volatile u32		sysTicks;

const u8	deBadBoys1[] = {	0x00, 0x00,
								0x00, 0x00,
								0x07, 0xc0,
								0x1f, 0xf0,
								0x3f, 0xf8,
								0x33, 0x98,
								0x3f, 0xf8,
								0x0c, 0x60,
								0x1b, 0xb0,
								0x30, 0x18,
								0x00, 0x00,
								0x00, 0x00 };

const u8	deBadBoys2[] = {	0x00, 0x00,
								0x00, 0x00,
								0x07, 0xc0,
								0x1f, 0xf0,
								0x3f, 0xf8,
								0x33, 0x98,
								0x3f, 0xf8,
								0x0c, 0x60,
								0x1b, 0xb0,
								0x0c, 0x60,
								0x00, 0x00,
								0x00, 0x00 };

void demoInit(void) {

i16		x, y, x1, y1, i, flip;


//	Demo Point

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);
	gdiDrawTextEx(180, 40, (pu8)"ARTEKIT", GDI_ROP_COPY);
	gdiDrawTextEx(161, 55, (pu8)"AK-STM32-LKIT", GDI_ROP_COPY);
	gdiDrawTextEx(172, 70, (pu8)"POINT DEMO", GDI_ROP_COPY);
	sysDelayMs(3000);
//	srand(sysTicks);
	for (i = 0; i < 5000; i++) {
		sysDelayMs(1);
		x = rand();	x = x % (VID_PIXELS_X - 1);
		y = rand();	y = y % VID_VSIZE - 1;
		gdiPoint(NULL,x,y,GDI_ROP_COPY);
	}
	sysDelayMs(3000);

//	Demo Line

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);
	gdiDrawTextEx(180, 40, (pu8)"ARTEKIT", GDI_ROP_COPY);
	gdiDrawTextEx(161, 55, (pu8)"AK-STM32-LKIT", GDI_ROP_COPY);
	gdiDrawTextEx(175, 70, (pu8)"LINE DEMO", GDI_ROP_COPY);
	sysDelayMs(3000);
//	srand(sysTicks);
	for (i = 0; i < 100; i++) {
		sysDelayMs(50);
		x = rand();	x = x % (VID_PIXELS_X - 1);
		y = rand();	y = y % VID_VSIZE - 1;
		x1 = rand();	x1 = x1 % (VID_PIXELS_X - 1);
		y1 = rand();	y1 = y1 % VID_VSIZE - 1;
		gdiLine(NULL,x,y,x1,y1,GDI_ROP_COPY);
	}
	sysDelayMs(3000);

//	Demo Square

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);
	gdiDrawTextEx(180, 40, (pu8)"ARTEKIT", GDI_ROP_COPY);
	gdiDrawTextEx(161, 55, (pu8)"AK-STM32-LKIT", GDI_ROP_COPY);
	gdiDrawTextEx(157, 70, (pu8)"RECTANGLE DEMO", GDI_ROP_COPY);
	sysDelayMs(3000);
//	srand(sysTicks);
	for (i = 0; i < 100; i++) {
		sysDelayMs(50);
		x = rand();	x = x % (VID_PIXELS_X - 1);
		y = rand();	y = y % VID_VSIZE - 1;
		x1 = rand();	x1 = x1 % 100;
		y1 = rand();	y1 = y1 % 100;
		gdiRectangle(x,y,x1,y1,GDI_ROP_COPY);
	}
	sysDelayMs(3000);

//	Demo Circle

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);
	gdiDrawTextEx(180, 40, (pu8)"ARTEKIT", GDI_ROP_COPY);
	gdiDrawTextEx(161, 55, (pu8)"AK-STM32-LKIT", GDI_ROP_COPY);
	gdiDrawTextEx(165, 70, (pu8)"CIRCLE DEMO", GDI_ROP_COPY);
	sysDelayMs(3000);
//	srand(sysTicks);
	for (i = 0; i < 200; i++) {
		sysDelayMs(20);
		x = rand();	x = x % (VID_PIXELS_X - 1);
		y = rand();	y = y % VID_VSIZE - 1;
		x1 = rand(); x1 = x1 % 80;
		gdiCircle(x,y,x1,GDI_ROP_COPY);
	}
	sysDelayMs(3000);

//	Demo Bitmap

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);
	gdiDrawTextEx(180, 40, (pu8)"ARTEKIT", GDI_ROP_COPY);
	gdiDrawTextEx(161, 55, (pu8)"AK-STM32-LKIT", GDI_ROP_COPY);
	gdiDrawTextEx(165, 70, (pu8)"BITMAP DEMO", GDI_ROP_COPY);
	sysDelayMs(3000);

	x = 100;
	y = 130;
	flip = 0;
	for (i = 0; i < 100; i++) {
		sysDelayMs(150);
		if (flip) {
			flip = 0;
			gdiBitBlt(NULL,x,y,15,12,(pu8) deBadBoys1,GDI_ROP_COPY);
		} else {
			flip = 1;
			gdiBitBlt(NULL,x,y,15,12,(pu8) deBadBoys2,GDI_ROP_COPY);
		}
		x += 2;
	}
	sysDelayMs(3000);

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);
	gdiDrawTextEx(180, 40, (pu8)"ARTEKIT", GDI_ROP_COPY);
	gdiDrawTextEx(161, 55, (pu8)"AK-STM32-LKIT", GDI_ROP_COPY);
	gdiDrawTextEx(115, 75, (pu8)"ARM CORTEX DEVELOPMENT BOARDS", GDI_ROP_COPY);

	gdiDrawTextEx(156, 90, (pu8)"WWW.ARTEKIT.EU", GDI_ROP_COPY);
	gdiDrawTextEx(141, 120, (pu8)"FREE GRAPHIC ENGINE", GDI_ROP_COPY);
	gdiDrawTextEx(165, 130, (pu8)"SOURCE CODE", GDI_ROP_COPY);

	while (1) {};


}


/* K&R rand function : return pseudo-random integer on 0..32767 */

static int				next;

int rand(void)
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next/65536) % 32768;
}
 
/* srand: set seed for rand() */
void srand(unsigned int seed)
{
	next = seed;
}