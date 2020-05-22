/***************************************************************************
 * STM32 VGA demo
 * Copyright (C) 2012 Artekit Italy
 * http://www.artekit.eu
 * Written by Ruben H. Meleca
 
### sys.h
 
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
#ifndef	__SYS_H
#define	__SYS_H

// #include "gdptypes.h"		// removed; use defs from stm32f4xx.h instead  KEL

//	Function definitions

void	SystemInit(void);			// borrowing the STM32F4 system init routines
u8		sysInitSystemTimer(void);
void	sysDelayMs(u32 dly);

#endif	// __SYS_H
