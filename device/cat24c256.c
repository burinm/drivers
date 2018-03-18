/* cat24c256.c - (c) 2016 - burin */

#include "cat24c256.h"
#include "../protocol/i2c.h"

//remember to inline all of this

//remember to check for page boundary

void device_cat24c256_open() {
    i2c_open();
    i2c_mem_device_reset();

//TODO: This needs to not be global - per device!!!
    i2c_set_page_size(DEVICE_I2C_CAT24C256_PAGE_SIZE);
}

uint8_t device_cat24c256_read_byte(uint16_t addr) {
    i2c_set_device_id(DEVICE_I2C_CAT24C256);
return i2c_device_read_random_byte(addr);
}

void device_cat24c256_write_byte(uint16_t addr, uint8_t b) {
    i2c_set_device_id(DEVICE_I2C_CAT24C256);
    i2c_device_write_byte(addr, b);
}

void device_cat24c256_write_page(uint16_t addy, uint8_t *b, size_t s) {
    i2c_device_write_bytes(addy, b, s);
}

void device_cat24c256_write_block(uint16_t addy, uint8_t b, size_t s) {
    i2c_device_write_block(addy, b, s);
}
