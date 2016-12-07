/* pcf8574a.c - (c) 2016 - burin */

#include "pcf8574a.h"
#include "i2c.h"

uint8_t io_direction;


void pcf8574a_open() {
    i2c_open();
    pcf8574a_write_port(0xff);
    io_direction=0xff;
}

void pcf8574a_reset() {
    pcf8574a_write_port(0xff);
    io_direction=0xff;
}

//Set pin high for input
void pcf8574a_io_direction(uint8_t pin, pcf8574a_io_direction_e d) {
uint8_t b;

    i2c_set_device_id(DEVICE_I2C_PCF8574A);

    if (pin > 7) { return; }
    b=pcf8574a_read_port();
    if (d == DIR_IN) {
        // Set bit
        b=b | (1<<pin);
        pcf8574a_write_port(b);
    }

    if (d == DIR_OUT) {
        // clear bit
        b=b & ~( 1<<pin);   
        pcf8574a_write_port(b);
    }

    io_direction=b;
}

void pcf8574a_write_port(uint8_t b) {
    i2c_set_device_id(DEVICE_I2C_PCF8574A);
    i2c_device_simple_write_byte(DEVICE_I2C_PCF8574A_ADDR,b);
}

uint8_t pcf8574a_read_port() {
    i2c_set_device_id(DEVICE_I2C_PCF8574A);
return i2c_device_simple_read_byte(DEVICE_I2C_PCF8574A_ADDR);;
}
