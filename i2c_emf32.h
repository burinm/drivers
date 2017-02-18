/* i2c_emf32.h - (c) 2017 - burin 
    EMF32 i2c "protocol" using builtin i2c hardware
        Non standard protocol half hardware/half software
*/

#ifndef __I2CEMF32_H__
#define __I2CEMF32_H__

#include "i2c.h"
#include <stdio.h>

void i2c_open();
void i2c_reset();
void i2c_set_device_id(uint8_t d);
void i2c_set_page_size(uint8_t s);
void i2c_start();
void i2c_stop();
void i2c_send_control_byte(uint8_t msb_addy ,i2c_action_e a);
void i2c_prot_setup_read_write(uint16_t addy, i2c_action_e rw);
uint8_t i2c_device_read_reg(uint8_t reg);
void i2c_device_write_reg(uint8_t reg, uint8_t data);
uint16_t i2c_device_read_reg16(uint8_t reg);
void i2c_device_write_reg16(uint8_t reg, uint16_t data);

#endif
