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
 * Adapted from codec.h
 * Created on: Jun 7, 2012
 * Author: Kumar Abhishek
 */

#ifndef __CODEC_CS4354_H
#define __CODEC_CS4354_H

#include "ch.h"
#include "hal.h"

#define CODEC_I2S_ENABLE rccEnableSPI3(FALSE)
#define CODEC_I2S_DISABLE rccDisableSPI3(FALSE)
#define CODEC_I2S SPI3

extern void codec_CS4354_hw_init(void);

extern void codec_CS4354_hw_reset(void);

extern void codec_CS4354_i2s_init_48k(void);

#endif /* CODEC_H_ */
