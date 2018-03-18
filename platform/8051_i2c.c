/* 8051_i2c.c - (c) 2016 - burin */

#include "8051_i2c.h"

static device_i2c_8051_t i2c_device;

void i2c_open_device() {
//TODO: extend for multiple devices
    i2c_device.id=DEVICE_IC2_8051_0_ID;
}

void i2c_set_device_type(uint8_t d) {
    i2c_device.type=d;
}

// i2c Interface implementation
void i2c_data_low() {
    DEVICE_I2C_8051_0_SDA = 0;
}

void i2c_data_high() {
    DEVICE_I2C_8051_0_SDA = 1;
}

void i2c_clock_low() {
    DEVICE_I2C_8051_0_SDC = 0;
}

void i2c_clock_high() {
    DEVICE_I2C_8051_0_SDC = 1;

}

i2c_level_e i2c_clock_read() {
    return ( DEVICE_I2C_8051_0_SDC == 0) ? LOW : HIGH;
}

i2c_level_e i2c_data_read() {
    return ( DEVICE_I2C_8051_0_SDA == 0) ? LOW : HIGH;
}

// end interface
