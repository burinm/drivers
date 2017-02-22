/* gecko_i2c.h - (c) 2017 - burin

   Leopard Gecko EMF32 board 

    Implements i2c.h for the LG990F256G 

    Using I2C1, location 0
         SCL = PC5
         SDA = PC4
*/

#ifndef __GECKO_I2C_H__
#define __GECKO_I2C_H__

#include "i2c.h"

#define GECKO_I2C_SDA_PORT       gpioPortC
#define GECKO_I2C_SDA_PORT_NUM   4 
#define GECKO_I2C_SCL_PORT       gpioPortC
#define GECKO_I2C_SCL_PORT_NUM   5 


// Implements interface in i2c.h
void i2c_open_device();

void i2c_data_low();
void i2c_data_high();

void i2c_clock_low();
void i2c_clock_high();

i2c_level_e i2c_clock_read();
i2c_level_e i2c_data_read();

void i2c_data_dir_in();
void i2c_data_dir_out();
// End implementation

// Other hardware specific functions for Gecko
uint8_t i2c_busy(); // Bus is busy, will be set on reset

void i2c_abort(); // Force i2c out of busy state
void i2c_cmd_start();
void i2c_cmd_stop();
void i2c_cmd_ack();
void i2c_cmd_nack();
void i2c_set_txdata(uint8_t tx);
uint8_t i2c_is_ack();
void i2c_clear_ack();
uint8_t i2c_get_rxdata();


#endif
