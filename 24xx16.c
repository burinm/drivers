#include "24xx16.h"
#include "i2c.h"

//remember to inline all of this

//remember to check for page boundary

void device_24XX16_open() {
    i2c_open();
    i2c_mem_device_reset();

//TODO: This needs to not be global - per device!!!
    i2c_set_page_size(DEVICE_I2C_24XX16_PAGE_SIZE);
}

uint8_t device_24XX16_read_byte(uint16_t addr) {
    i2c_set_device_id(DEVICE_I2C_24LC16B);
return i2c_device_read_random_byte(addr);
}

void device_24XX16_write_byte(uint16_t addr, uint8_t b) {
    i2c_set_device_id(DEVICE_I2C_24LC16B);
    i2c_device_write_byte(addr, b);
}

void device_24XX16_write_page(uint16_t addy, uint8_t *b, size_t s) {
    i2c_device_write_bytes(addy, b, s);
}

void device_24XX16_write_block(uint16_t addy, uint8_t b, size_t s) {
    i2c_device_write_block(addy, b, s);
}
