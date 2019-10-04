/**
 * Copyright (C) 2016 Ricard Wanderlof
 *
 * This file is part of Axoloti.
 *
 * 24Cxx EEPROM driver adapted from Timon Wong's ChibiOS-EEPROM driver.
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

/*
  Copyright (c) 2013 Timon Wong

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/*
  Copyright 2012 Uladzimir Pylinski aka barthess.
  You may use this work without restrictions, as long as this notice is included.
  Copyright 2017 Ricard Wanderlof.
  The work is provided "as is" without warranty of any kind, neither express nor implied.
*/

/*****************************************************************************
 * DATASHEET NOTES
 *****************************************************************************
Write cycle time (byte or page) - 5 ms

Note:
  Page write operations are limited to writing bytes within a single physical
  page, regardless of the number of bytes actually being written. Physical page
  boundaries start at addresses that are integer multiples of the page buffer
  size (or page size and end at addresses that are integer multiples of
  [page size]. If a Page Write command attempts to write across a physical
  page boundary, the result is that the data wraps around to the beginning of
  the current page (overwriting data previously stored there), instead of
  being written to the next page as might be expected.
*********************************************************************/

#include <string.h>

#include "ch.h"
#include "hal.h"

#include "eeprom.h"

#include "axoloti.h" // for LogTextMessage

#if HAL_USE_I2C || defined(__DOXYGEN__)

typedef struct {
  uint32_t size; /* total 24Cxx size */
  uint32_t pagesize; /* size of one 24Cxx page */
  systime_t write_time; /* write time for page write (ms) */
  i2caddr_t addr; /* Non-configurable chip address (normally 0xA0 >> 1) */
  I2CConfig i2cfg;
} EepromConfig_t;

/* The pagesize memeber must be no larger than PAGESIZE_MAX for any chip */
static EepromConfig_t EepromConfigs[EEPROM_TYPES] =
	{ { 65536, 128, 5, 0xa0 >> 1,
	    { OPMODE_I2C, 400000, FAST_DUTY_CYCLE_2 } } }; /* 24C512 */

typedef struct {
  EepromConfig_t *eeprom;
  I2CDriver     *i2cp;
  i2caddr_t     pinaddr; /* pin configured address */
  uint8_t	*pagebuf;
} I2CEepromConfig_t;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#if defined(SAM7_PLATFORM)
#define EEPROM_I2C_CLOCK (MCK / (((i2cp->config->cwgr & 0xFF) + ((i2cp->config->cwgr >> 8) & 0xFF)) * (1 << ((i2cp->config->cwgr >> 16) & 7)) + 6))
#else
#define EEPROM_I2C_CLOCK (i2cp->config->clock_speed)
#endif

#define ADDR_SIZE 2 // # address bytes in EEPROM commands

#define PAGESIZE_MAX 128 // maximum size of EEPROM page that we support

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */
/**
 * @brief   Split one uint16_t address to two uint8_t.
 *
 * @param[in] txbuf pointer to driver transmit buffer
 * @param[in] addr  uint16_t address
 */
#define eeprom_split_addr(txbuf, addr){                                       \
    (txbuf)[0] = ((uint8_t)((addr >> 8) & 0xFF));                              \
    (txbuf)[1] = ((uint8_t)(addr & 0xFF));                                     \
  }

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * @brief     Calculates requred timeout.
 */
static systime_t calc_timeout(I2CDriver *i2cp, size_t txbytes, size_t rxbytes) {
  const uint32_t bitsinbyte = 10;
  uint32_t tmo;
  tmo = ((txbytes + rxbytes + 1) * bitsinbyte * 1000);
  tmo /= EEPROM_I2C_CLOCK;
  tmo += 10; /* some additional milliseconds to be safer */
  return MS2ST(tmo);
}

/**
 * @brief   EEPROM read routine.
 *
 * @param[in] eepcfg    pointer to configuration structure of eeprom file
 * @param[in] offset    addres of 1-st byte to be read
 * @param[in] len       number of bytes to be red
 */
msg_t eeprom_read(const I2CEepromConfig_t *eepcfg, uint32_t offset, size_t len)
{
  msg_t status = RDY_RESET;
  systime_t tmo = calc_timeout(eepcfg->i2cp, 2, len);

  chDbgCheck(((len <= eepcfg->eeprom->size) &&
	     ((offset + len) <= eepcfg->eeprom->size)),
             "out of device bounds");

  /* Put address bytes at start of pagebuf */
  eeprom_split_addr(eepcfg->pagebuf, offset);

#if I2C_USE_MUTUAL_EXCLUSION
  i2cAcquireBus(eepcfg->i2cp);
#endif

  status = i2cMasterTransmitTimeout(eepcfg->i2cp,
				    eepcfg->eeprom->addr + eepcfg->pinaddr,
                                    eepcfg->pagebuf, ADDR_SIZE,
				    eepcfg->pagebuf + 2, len, tmo);

#if I2C_USE_MUTUAL_EXCLUSION
  i2cReleaseBus(eepcfg->i2cp);
#endif

  return status;
}

/**
 * @brief   EEPROM write routine.
 * @details Function writes data to EEPROM.
 * @pre     Data must be fit to single EEPROM page.
 *
 * @param[in] eepcfg  pointer to configuration structure of eeprom file
 * @param[in] offset  addres of 1-st byte to be write
 * @param[in] len     number of bytes to be written
 */
msg_t eeprom_write(const I2CEepromConfig_t *eepcfg, uint32_t offset, size_t len)
{
  msg_t status = RDY_RESET;
  systime_t tmo = calc_timeout(eepcfg->i2cp, (len + ADDR_SIZE), 0);

  chDbgCheck(((len <= eepcfg->eeprom->size) &&
	     ((offset + len) <= eepcfg->eeprom->size)),
             "out of device bounds");
  chDbgCheck(((offset / eepcfg->eeprom->pagesize) ==
              ((offset + len - 1) / eepcfg->eeprom->pagesize)),
             "data can not be fitted in single page");

  /* write address bytes */
  eeprom_split_addr(eepcfg->pagebuf, offset);
  /* data bytes already in buffer, written by application */

#if I2C_USE_MUTUAL_EXCLUSION
  i2cAcquireBus(eepcfg->i2cp);
#endif

  status = i2cMasterTransmitTimeout(eepcfg->i2cp,
				    eepcfg->eeprom->addr + eepcfg->pinaddr,
                                    eepcfg->pagebuf, len + ADDR_SIZE, NULL, 0,
				    tmo);

#if I2C_USE_MUTUAL_EXCLUSION
  i2cReleaseBus(eepcfg->i2cp);
#endif

  /* wait until EEPROM process data */
  chThdSleep(eepcfg->eeprom->write_time);

  return status;
}

/****************************************************************************
 * Patch API
 ****************************************************************************/

// We need to keep the pagebuf here and not in the application, as all
// application data is on the stack and hence in CCM, which is not DMAable
static uint8_t pagebuf[PAGESIZE_MAX + ADDR_SIZE];

/* For ref. only
static I2CEepromConfig_t P6_EepromConfig =
	{ &EepromConfigs[EEPROM_TYPE_24C512], &I2CD1, 0, &pagebuf[0] };
*/

// For now we allow a single instance, and this is it.
static I2CEepromConfig_t I2CEepromConfig;

enum eeprom_op { EEPROM_NONE, EEPROM_READ, EEPROM_WRITE };

typedef struct {

  uint32_t addr; /* address in eeprom */
  size_t len; /* length of data. Must be multiple of page size */
  enum eeprom_op op;
  EepromStatus_t status;
} EepromCmd_t;

EepromCmd_t EepromCmd;

/* Thread for EEPROM read/write */
static WORKING_AREA(waThreadEeprom, 256);
static Thread *pThreadEeprom;

/**
 * @brief   EEPROM thread function.
 *
 * @param[in] arg  unused
 */
static msg_t ThreadEeprom(void *arg)
{
  msg_t status = RDY_OK;

  (void)arg;

#if CH_USE_REGISTRY
  chRegSetThreadName("eeprom");
#endif

  while (1) {
    size_t offs;
    chEvtWaitAny((eventmask_t)1);

    if (!I2CEepromConfig.i2cp) continue; /* Nothing set up, nothing to do. */

    int pagesize = I2CEepromConfig.eeprom->pagesize;

    switch (EepromCmd.op)
    {
      case EEPROM_READ:
        for (offs = 0; offs < EepromCmd.len; offs += pagesize) {
LogTextMessage("EEprom read: bus 0x%08lx, devaddr %d, addr %u, len %d", I2CEepromConfig.i2cp, I2CEepromConfig.pinaddr, EepromCmd.addr + offs, pagesize);
	  status = eeprom_read(&I2CEepromConfig,
			       EepromCmd.addr + offs, pagesize);
          if (status != RDY_OK) break;
	}
LogTextMessage("EEprom read: done: status = %d, errors = 0x%02x",  status, i2cGetErrors(I2CEepromConfig.i2cp));
	EepromCmd.status.ok = (status == RDY_OK);
	EepromCmd.op = EEPROM_NONE;
        EepromCmd.status.busy = 0; /* signal done */
	break;
      case EEPROM_WRITE:
        for (offs = 0; offs < EepromCmd.len; offs += pagesize) {
LogTextMessage("EEprom write: bus 0x%08lx, devaddr %d, addr %u, len %d", I2CEepromConfig.i2cp, I2CEepromConfig.pinaddr, EepromCmd.addr + offs, pagesize);
	  status = eeprom_write(&I2CEepromConfig,
				EepromCmd.addr + offs, pagesize);
          if (status != RDY_OK) break;
	}
LogTextMessage("EEprom write: done: status = %d, errors = 0x%02x",  status, i2cGetErrors(I2CEepromConfig.i2cp));
	EepromCmd.status.ok = (status == RDY_OK);
	EepromCmd.op = EEPROM_NONE;
        EepromCmd.status.busy = 0; /* signal done */
	break;
      case EEPROM_NONE:
      default:
        break;
    }
  }
  return (msg_t)0;
}

/**
 * @brief   EEPROM init. Just start EEPROM thread.
 *
 */
void eeprom_init(void)
{
  I2CEepromConfig.i2cp = NULL; /* no I2C bus configured yet. */

  pThreadEeprom = chThdCreateStatic(waThreadEeprom, sizeof(waThreadEeprom),
				    NORMALPRIO, ThreadEeprom, NULL);
}

/**
 * @brief   Patch API: EEPROM setup.
 *
 * @param[in] type     EEPROM type (24LC512 etc)
 * @param[in] bus      Pointer to driver structure (I2CDx), representing port
 * @param[in] pinaddr  Address pins set on EEPROM (i.e. A0..A2)
 */
void *eeprom_setup(enum EepromTypes type, I2CDriver *bus, uint8_t pinaddr)
{
/* Done by object or init
  palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
  palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
*/

  I2CEepromConfig.eeprom = &EepromConfigs[type];
  I2CEepromConfig.i2cp = bus;
  I2CEepromConfig.pinaddr = pinaddr;
  I2CEepromConfig.pagebuf = pagebuf;

  i2cStart(I2CEepromConfig.i2cp, &I2CEepromConfig.eeprom->i2cfg);

  return &I2CEepromConfig;
}

/**
 * @brief   Patch API: EEPROM teardown.
 *
 * @param[in] handle   handle to EEPROM instance
 */
void eeprom_teardown(void *handle)
{
  if (I2CEepromConfig.i2cp) i2cStop(I2CEepromConfig.i2cp);

  I2CEepromConfig.i2cp = NULL; // deconfigured
}

/**
 * @brief   Patch API: Get EEPROM buffer pointer.
 *
 * @param[in] handle    handle to Eeprom config structure
 * @param[in] bufsize   optional return value with buffer size
 */
uint8_t *eeprom_get_pagebuf(void *handle, int *bufsize)
{
  I2CEepromConfig_t *config = handle;

  if (config != &I2CEepromConfig) return NULL;

  if (bufsize) *bufsize = config->eeprom->pagesize;

  return config->pagebuf + 2;
}

/**
 * @brief   Patch API: EEPROM write.
 *
 * @param[in] handle    handle to Eeprom config structure
 * @param[in] addr      address in EEPROM of 1-st byte to be written
 * @param[in] len       number of bytes to be written
 */
EepromStatus_t *eeprom_write_data(void *handle, uint32_t addr, size_t len)
{
  if (handle != &I2CEepromConfig) return NULL;
  if (EepromCmd.status.busy) return NULL;

  chDbgCheck(len % I2CEepromConfig.eeprom->pagesize == 0,
	     "len not multiple of page size");
  EepromCmd.addr = addr;
  EepromCmd.len = len;
  EepromCmd.status.busy = 1;
  EepromCmd.op = EEPROM_WRITE;
  chEvtSignal(pThreadEeprom, (eventmask_t)1);

  return &EepromCmd.status;
}

/**
 * @brief   Patch API: EEPROM read.
 *
 * @param[in] handle    handle to Eeprom config structure
 * @param[in] addr      address in EEPROM of 1-st byte to be read
 * @param[in] len       number of bytes to be red
 */
EepromStatus_t *eeprom_read_data(void *handle, uint32_t addr, size_t len)
{
  if (handle != &I2CEepromConfig) return NULL;
  if (EepromCmd.status.busy) return NULL;

  chDbgCheck(len % I2CEepromConfig.eeprom->pagesize == 0,
	     "len not multiple of page size");
  EepromCmd.addr = addr;
  EepromCmd.len = len;
  EepromCmd.status.busy = 1;
  EepromCmd.op = EEPROM_READ;
  chEvtSignal(pThreadEeprom, (eventmask_t)1);

  return &EepromCmd.status;
}

#endif /* HAL_USE_I2C */
