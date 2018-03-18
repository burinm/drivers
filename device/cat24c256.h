/* cat24c256.h - (c) 2016 - burin

    CAT24C256 i2c EEPROM driver

    Extends i2c.h

    TODO - *not working* This eeprom requires 16bit addressing
            need to rework i2c base driver

            Also, having problems with ACK
*/

#ifndef __CAT24C256_H__
#define __CAT24C256_H__



#include <stdint.h>
#include <stdio.h>

#define DEVICE_I2C_CAT24C256  0xA //1010b
#define DEVICE_I2C_CAT24C256_PAGE_SIZE 0x40
#define DEVICE_I2C_CAT24C25_MEM_SIZE 0x8000


// Called to initialize and reset EEPROM
void device_cat24c256_open();

// Read byte from EEPROM
uint8_t device_cat24c256_read_byte(uint16_t addr);
// Write byte to EEPROM
void device_cat24c256_write_byte(uint16_t addr, uint8_t b);

// Page write data. Takes data from memory at b, for s bytes
void device_cat24c256_write_page(uint16_t addy, uint8_t *b, size_t s);

// Write same character into block of memory. Write byte b, s times
void device_cat24c256_write_block(uint16_t addy, uint8_t b, size_t s);

#endif
