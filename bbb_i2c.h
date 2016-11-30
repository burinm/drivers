#ifndef __BBB_I2C_H__
#define __BBB_I2C_H__

#include "i2c.h"

/* BeagleBone Black SPI implementation

    Implements i2c.h for the BBB 3.8.13-bone47

*/

void i2c_open_device();

void i2c_data_low();
void i2c_data_high();

void i2c_clock_low();
void i2c_clock_high();

i2c_level_e i2c_clock_read();
i2c_level_e i2c_data_read();

#endif
