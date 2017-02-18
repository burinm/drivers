#include "tsl2651.h"
#include "i2c.h"

void tsl2651_open() {
    i2c_open();
    i2c_reset();
}

uint8_t tsl2651_read_register(uint8_t reg) {
    i2c_set_device_id(DEVICE_I2C_TSL2651);
return i2c_device_read_reg(reg);
} 

void tsl2651_write_register(uint8_t reg, uint8_t b) {
    i2c_set_device_id(DEVICE_I2C_TSL2651);
    i2c_device_write_reg(reg, b);
}

uint16_t tsl2651_read_register16(uint16_t reg) {
    i2c_set_device_id(DEVICE_I2C_TSL2651);
return i2c_device_read_reg16(reg);
} 

void tsl2651_write_register16(uint16_t reg, uint16_t b) {
    i2c_set_device_id(DEVICE_I2C_TSL2651);
    i2c_device_write_reg16(reg, b);
}


