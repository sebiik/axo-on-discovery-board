/**
 * Copyright (C) 2013, 2014 Johannes Taelman
 *
 * This file is part of Axoloti.
 *
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
#ifndef __AXOLOTI_H
#define __AXOLOTI_H

#include <fastmath.h>
#include <stdint.h>

#include "axoloti_math.h"

#include "axoloti_oscs.h"
#include "axoloti_filters.h"
#include "limits.h"
#include "ui.h"
#include "midi.h"

#include "sdcard.h"

#include "sysmon.h"

#if (USE_EXTERNAL_EEPROM)
#include "eeprom.h" //seb
#endif

void axoloti_init(void);

extern void codec_WM8731_i2s_init_48k(void);
extern void codec_WM8731_hw_reset(void);
extern void codec_WM8731_hw_init(void);
extern void codec_WM8731_writeReg(uint8_t addr, uint16_t data);
extern void codec_WM8731_lineInVolCtl(uint8_t vol);
extern void codec_WM8731_headphoneVolCtl(uint16_t vol);
extern void codec_WM8731_pwrCtl(uint8_t pwr);
extern void codec_WM8731_muteCtl(uint8_t mute);
extern void codec_WM8731_activeCtl(uint8_t active);
extern void codec_WM8731_I2CStart(void);
extern void codec_WM8731_I2CStop(void);
extern void codec_WM8731_sendStandardCfg(void);

void LogTextMessage(const char* format, ...);

#endif
