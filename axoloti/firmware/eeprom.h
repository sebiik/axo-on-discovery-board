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

#ifndef __EPROM_H
#define __EPROM_H

enum EepromTypes { EEPROM_TYPE_24C512 = 0, EEPROM_TYPES };

typedef struct {
  int busy; /* 1 while operation in progress */
  int ok; /* returned status */
} EepromStatus_t;

extern uint8_t eeprom_buffer[128];

/* Internal API */
void eeprom_init(void);

/* Patch API */
void *eeprom_setup(enum EepromTypes type, I2CDriver *bus, uint8_t pinaddr);
void eeprom_teardown(void *handle);

uint8_t *eeprom_get_pagebuf(void *handle, int *buflen);

EepromStatus_t *eeprom_write_data(void *handle, uint32_t addr, size_t len);

EepromStatus_t *eeprom_read_data(void *handle, uint32_t addr,  size_t len);

#endif /* __EPROM_H */
