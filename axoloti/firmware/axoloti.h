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

extern bool_t codec_WM8731_writeReg(uint8_t addr, uint16_t data);

void LogTextMessage(const char* format, ...);

#endif
