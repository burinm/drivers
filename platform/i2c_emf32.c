/* i2c_emf32.c - (c) 2017 - burin 
    EMF32 i2c "protocol" using builtin i2c hardware
        Non standard protocol half hardware/half software
*/

#include "i2c.h"
#include "i2c_emf32.h"
#include "gecko_i2c.h"
#include <stdio.h>

void i2c_open() {
    i2c_open_device();
}

void i2c_close() {
    i2c_close_device();
}

void i2c_reset() {
uint8_t i;
    if (i2c_busy()) {
        i2c_abort();
    }

}

void i2c_set_device_id(uint8_t d) {
    i2c_device_id=d;
}

void i2c_set_page_size(uint8_t s) {
    i2c_page_size=s;
}

void i2c_start() {
    i2c_cmd_start();
}

void i2c_stop() { 
    i2c_cmd_stop();
}

// Blocking ACKs - fix to not block after testing
uint8_t i2c_ack_acknowledge() {
    while(i2c_is_ack() == 0);
    i2c_clear_ack();
return 1;
}


void i2c_send_control_byte(uint8_t msb_addy ,i2c_action_e a) {
    uint8_t tx=0;
    uint8_t d_id= i2c_device_id & I2C_ID_MASK;

    tx = msb_addy;
    tx <<=I2C_ID_BITS; 
    tx += d_id;
    tx <<=1;
    tx += (a == READ) ? HIGH:LOW;

    i2c_set_txdata(tx);
}


void i2c_prot_setup_read_write(uint16_t addy, i2c_action_e rw) {

    i2c_send_control_byte( ((addy & I2C_MSB_MASK) >> I2C_LSB_BITS),
                            (rw == READ) ? HIGH:LOW );
}

uint8_t i2c_device_read_reg(uint16_t addy, uint8_t reg) {
uint8_t b;
    i2c_start(); //This can be put after TXfill as enhancement later...
    i2c_prot_setup_read_write(addy, WRITE);
    i2c_ack_acknowledge();

    // Set "Command Code"
    i2c_set_txdata(reg);
    i2c_ack_acknowledge();

    i2c_start();
    i2c_prot_setup_read_write(addy, READ);
    i2c_ack_acknowledge();

    b =i2c_get_rxdata();
    i2c_cmd_nack(); 
    i2c_stop();
return b;
}

void i2c_device_write_reg(uint16_t addy, uint8_t reg, uint8_t data) {
    i2c_start();
    i2c_prot_setup_read_write(addy, WRITE);
    i2c_ack_acknowledge();

    // Set "Command Code"
    i2c_set_txdata(reg);
    i2c_ack_acknowledge();

    i2c_set_txdata(data);
    i2c_ack_acknowledge();
    i2c_stop();
}

// Untested
uint16_t i2c_device_read_reg16(uint16_t addy, uint8_t reg) {
uint16_t b;
    i2c_start();
    i2c_prot_setup_read_write(addy, WRITE);
    i2c_ack_acknowledge();

    // Set "Command Code", which is just the register
    i2c_set_txdata(reg);
    i2c_ack_acknowledge();

    i2c_prot_setup_read_write(addy, READ);
    i2c_start();
    i2c_ack_acknowledge();
    i2c_cmd_ack(); 

    b =i2c_get_rxdata();
    i2c_cmd_ack(); 
    b += (i2c_get_rxdata() <<8);
    i2c_cmd_ack(); 
    i2c_stop();
return b;
}

// Untested
void i2c_device_write_reg16(uint16_t addy, uint8_t reg, uint16_t data) {
    i2c_start();
    i2c_prot_setup_read_write(addy, WRITE);
    i2c_ack_acknowledge();

    // Set "Command Code", which is just the register
    i2c_set_txdata(reg);
    i2c_ack_acknowledge();

//Put in defines....
    i2c_set_txdata(data & 0xf);
    i2c_ack_acknowledge();
    i2c_set_txdata(data >> 4);
    i2c_ack_acknowledge();
    i2c_stop();
}
