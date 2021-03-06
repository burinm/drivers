/* 24xx16.h - (c) 2016 - burin

    24LC16B i2c EEPROM driver

    Extends i2c.h
*/

#ifndef __24XX16_H__
#define __24XX16_H__


#include <stdint.h>
#include <stdio.h>

#define DEVICE_I2C_24LC16B  0xA //1010b
#define DEVICE_I2C_24XX16_PAGE_SIZE 0x10
#define DEVICE_I2C_24XX16_MEM_SIZE 0x800

// Called to initialize and reset EEPROM
void device_24XX16_open();

// Read byte from EEPROM
uint8_t device_24XX16_read_byte(uint16_t addr);
// Write byte to EEPROM
void device_24XX16_write_byte(uint16_t addr, uint8_t b);

// Page write data. Takes data from memory at b, for s bytes
void device_24XX16_write_page(uint16_t addy, uint8_t *b, size_t s);

// Write same character into block of memory. Write byte b, s times
void device_24XX16_write_block(uint16_t addy, uint8_t b, size_t s);

#endif
