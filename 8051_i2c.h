#ifndef __8051_I2C_H__
#define __8051_I2C_H__

/* 8051 i2c implementation

    implements i2c.h
*/

#include <stdint.h>
#include <mcs51reg.h>
#include "i2c.h"

typedef struct {
        uint8_t id;
        uint8_t type;
} device_i2c_8051_t;

#define DEVICE_IC2_8051_0_ID    (0x0)
#define DEVICE_I2C_8051_0_SDA   (P1_6)
#define DEVICE_I2C_8051_0_SDC   (P1_7)

// Interface functions, see i2c.h
void i2c_open_device();
void i2c_set_device_type(uint8_t d);

void i2c_data_low();
void i2c_data_high();

void i2c_clock_low();
void i2c_clock_high();

i2c_level_e i2c_clock_read();
i2c_level_e i2c_data_read();

// end interface

#endif
