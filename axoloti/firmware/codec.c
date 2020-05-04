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

#include "codec.h"
#include "axoloti_defines.h"


#if (BOARD_STM32F4DISCOVERY)
#include "codec_CS43L22.h"

#elif (BOARD_STM32F4DISCOVERY_WM8731)
#include "codec_WM8731.h"

#endif

int32_t buf[BUFSIZE*2] __attribute__ ((section (".sram2")));
int32_t buf2[BUFSIZE*2] __attribute__ ((section (".sram2")));
int32_t rbuf[BUFSIZE*2] __attribute__ ((section (".sram2")));
int32_t rbuf2[BUFSIZE*2] __attribute__ ((section (".sram2")));

void codec_init(void) {

#if (BOARD_STM32F4DISCOVERY)
  codec_CS43L22_i2s_init_48k();
  codec_CS43L22_hw_init();
  codec_CS43L22_pwrCtl(1);

#elif (BOARD_STM32F4DISCOVERY_WM8731)
  codec_WM8731_i2s_init_48k();
  codec_WM8731_hw_init();

#else
#error "BOARD_ not defined"
#endif
}

void codecStop(void) {
}

void codec_clearbuffer(void) {
  int i;
  for(i=0;i<BUFSIZE*2;i++){
    buf[i]=0;
    buf2[i]=0;
  }
}

#if (BOARD_STM32F4DISCOVERY)
#include "codec_CS43L22.c"
#elif (BOARD_STM32F4DISCOVERY_WM8731)
#include "codec_WM8731.c"
#endif
