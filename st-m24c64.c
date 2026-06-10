/*
 * st-m24c64.c
 *
 *  Created on: Jun 2, 2026
 *      Author: Patsaoglou P.
 */

#include <st-m24c64.h>

void eeprom_read_data(I2C_HandleTypeDef *hi2c, uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{
	uint16_t page_idx = page;
	uint16_t end_page = page + ((size+offset)/EEPROM_PAGE_SIZE);

	uint16_t pages_to_read = (end_page-page_idx) + 1;
	uint16_t pos=0;

	for (int i=0; i<pages_to_read; i++)
	{
		uint16_t eeprom_address = page_idx<<EEPROM_PAGE_BITS | offset;
		uint16_t bytes_remaining = bytes_to_rw(size, offset);
		HAL_I2C_Mem_Read(hi2c, EEPROM_ADD, eeprom_address, 2, &data[pos], bytes_remaining, 1000);

		page_idx += 1;
		offset = 0;
		size = size-bytes_remaining;
		pos += bytes_remaining;
	}
}


void eeprom_write_data(I2C_HandleTypeDef *hi2c, uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{
	uint16_t page_idx = page;
	uint16_t end_page = page + ((size+offset)/EEPROM_PAGE_SIZE);

	uint16_t pages_to_write = (end_page-page_idx) + 1;
	uint16_t pos=0;

	for (int i=0; i<pages_to_write; i++)
	{

		uint16_t eeprom_address = page_idx<<EEPROM_PAGE_BITS | offset;
		uint16_t bytes_remaining = bytes_to_rw(size, offset);

		HAL_I2C_Mem_Write(hi2c, EEPROM_ADD, eeprom_address, 2, &data[pos], bytes_remaining, 1000);

		page_idx += 1;
		offset = 0;
		size = size-bytes_remaining;
		pos += bytes_remaining;

		HAL_Delay (5);
	}
}

void eeprom_full_erase(I2C_HandleTypeDef *hi2c)
{
	uint8_t data[EEPROM_PAGE_SIZE];
	memset(data,0xff,EEPROM_PAGE_SIZE);

	// hole page erase
	for (int i=0; i<EEPROM_PAGE_NUM; i++)
	{
		uint16_t eeprom_address = i<<EEPROM_PAGE_BITS;

		HAL_I2C_Mem_Write(hi2c, EEPROM_ADD, eeprom_address, 2, data, EEPROM_PAGE_SIZE, 1000);

		HAL_Delay (5);
	}
}

uint16_t bytes_to_rw (uint16_t size, uint16_t offset)
{
	if ((size+offset)<EEPROM_PAGE_SIZE) return size;
	else return EEPROM_PAGE_SIZE-offset;
}
