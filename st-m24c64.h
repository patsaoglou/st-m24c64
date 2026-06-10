/*
 * st-m24c64.h
 *
 *  Created on: Jun 2, 2026
 *      Author: Patsaoglou P.
 */

#ifndef INC_ST_M24C64_H_
#define INC_ST_M24C64_H_

#include "stm32f4xx_hal.h"
#include <string.h>

#define EEPROM_ADD 			(0xA0)

#define EEPROM_PAGE_SIZE	32
#define EEPROM_PAGE_BITS	5
#define EEPROM_PAGE_NUM		256

void eeprom_read_data(I2C_HandleTypeDef *hi2c, uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void eeprom_write_data(I2C_HandleTypeDef *hi2c, uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void eeprom_full_erase(I2C_HandleTypeDef *hi2c);

uint16_t bytes_to_rw(uint16_t size, uint16_t offset);

#endif /* INC_ST_M24C64_H_ */
