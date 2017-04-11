#include "mma8452q.h"

void mma8452q_open() {
    i2c_set_device_id(DEVICE_I2C_MMA8452Q);
    i2c_open();
    i2c_reset();
}

void mma8452q_close() {
    i2c_close();
}

void mma8452q_on(uint8_t on) {
}

void mma8452q_int_clear() {
}

uint8_t mma8452q_read_register(uint8_t reg) {
return i2c_device_read_reg(TSL2651_ADDRESS, reg);
}

void mma8452q_write_register(uint8_t reg, uint8_t b) {
    i2c_device_write_reg(TSL2651_ADDRESS, reg, b);
}

