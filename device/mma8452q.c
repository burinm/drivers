#include "mma8452q.h"

void mma8452q_open() {
    i2c_set_device_id(DEVICE_I2C_MMA8452Q);
    i2c_open();
    i2c_reset();
}

void mma8452q_close() {
    i2c_close();
}

uint8_t mma8452q_on(uint8_t on) {
uint8_t id;
    if (on) {
        id = mma8452q_read_register(MMA8452Q_REG_WHO_AM_I);
        if (id == MMA8452Q_WHO_AM_I) {
            return 1;
        } else {
            return 0;
        }
    }
return 0;
}

void mma8452q_int_clear() {
}

uint8_t mma8452q_read_register(uint8_t reg) {
return i2c_device_read_reg(MMA8452Q_ADDRESS, reg);
}

void mma8452q_write_register(uint8_t reg, uint8_t b) {
    i2c_device_write_reg(MMA8452Q_ADDRESS, reg, b);
}

