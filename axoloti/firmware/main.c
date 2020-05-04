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

#include "axoloti_defines.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "shell.h"
#include "string.h"
#include <stdio.h>

#ifdef USE_EXTERNAL_EEPROM //seb
#include "eeprom.h" //seb
#endif //seb

#include "codec.h"
#include "ui.h"
#include "midi.h"
#include "sdcard.h"
#include "patch.h"
#include "pconnection.h"
#include "axoloti_control.h"
#include "axoloti_math.h"
#include "axoloti_board.h"
#include "exceptions.h"
#include "watchdog.h"

#include "chprintf.h"
#include "usbcfg.h"
#include "sysmon.h"

/*===========================================================================*/
/* Initialization and main thread.                                           */
/*===========================================================================*/


#define ENABLE_SERIAL_DEBUG 1

#ifdef ENABLE_USB_HOST
#error conflicting pins: USB_OTG_HS and I2S
#endif

// void ToggleGreen(void) {
//   palSetPadMode(GPIOD, 12, PAL_MODE_OUTPUT_PUSHPULL); palTogglePad(GPIOD, 12);
// }
// void ToggleOrange(void) {
//   palSetPadMode(GPIOD, 13, PAL_MODE_OUTPUT_PUSHPULL); palTogglePad(GPIOD, 13);
// }
// void ToggleRed(void) {
//   palSetPadMode(GPIOD, 14, PAL_MODE_OUTPUT_PUSHPULL); palTogglePad(GPIOD, 14);
// }
// void ToggleBlue(void) {
//   palSetPadMode(GPIOD, 15, PAL_MODE_OUTPUT_PUSHPULL); palTogglePad(GPIOD, 15);
// }

int main(void) {
  // copy vector table to SRAM1!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnonnull"
  memcpy((char *)0x20000000, (const char)0x00000000, 0x200);
#pragma GCC diagnostic pop
  // remap SRAM1 to 0x00000000
  SYSCFG->MEMRMP |= 0x03;

  halInit();
  chSysInit();
  sdcard_init();
  sysmon_init();

#if ENABLE_SERIAL_DEBUG
// SD2 for serial debug output
  palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7) | PAL_MODE_INPUT); // RX
  palSetPadMode(GPIOA, 2, PAL_MODE_OUTPUT_PUSHPULL); // TX
  palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7)); // TX
// 115200 baud
  static const SerialConfig sd2Cfg = {115200,
        0, 0, 0};
  sdStart(&SD2, &sd2Cfg);
  chprintf((BaseSequentialStream * )&SD2,"Hello world!\r\n");
#endif

  exception_init();

  InitPatch0();

  InitPConnection();

  // display SPI CS?
  palSetPadMode(GPIOC, 1, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(GPIOC, 1);

  chThdSleepMilliseconds(10);

  palSetPadMode(SW2_PORT, SW2_PIN, PAL_MODE_INPUT_PULLDOWN);

  axoloti_board_init();
  adc_init();

#if (USE_EXTERNAL_EEPROM)
  //seb
  eeprom_init();
#endif

  axoloti_math_init();
  midi_init();
  start_dsp_thread();
  codec_init();
  if (!palReadPad(SW2_PORT, SW2_PIN)) { // button S2 not pressed
//    watchdog_init();
    chThdSleepMilliseconds(1);
  }

  ui_init();

  if (!exception_check()) {
    // only try booting a patch when no exception is to be reported

    sdcard_attemptMountIfUnmounted();
    if (fs_ready && !palReadPad(SW2_PORT, SW2_PIN)){
      // button S2 not pressed
      LoadPatchStartSD();
    }

    // if no patch booting or running yet
    // try loading from flash
    if (patchStatus == STOPPED) {
      if (!palReadPad(SW2_PORT, SW2_PIN)) // button S2 not pressed
        LoadPatchStartFlash();
    }
  }

  while (1) {
    chThdSleepMilliseconds(1000);
  }
}

void HAL_Delay(unsigned int n) {
  chThdSleepMilliseconds(n);
}

void _sbrk(void) {
  while (1) {
  }
}
