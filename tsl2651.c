#include "tsl2651.h"
#include "i2c.h"
#include "i2c_emf32.h"

void tsl2651_open() {
    i2c_set_device_id(DEVICE_I2C_TSL2651);
    i2c_open();
    i2c_reset();
}

void tsl2651_on() {

    i2c_cmd_start();
    i2c_prot_setup_read_write(TSL2651_SEL_ADDR_FLOAT << I2C_ID_MSB_BIT_MASK, WRITE);
    i2c_ack_acknowledge();
    i2c_set_txdata(TSL2651_ADDR_CONTROL | TSL2651_REG_CMD);
    i2c_ack_acknowledge();

    i2c_set_txdata(TSL2651_CONTROL_POWER_MASK);
    i2c_ack_acknowledge();
    i2c_cmd_stop();

}

uint8_t tsl2651_read_register(uint16_t addy, uint8_t reg) {
return i2c_device_read_reg(TSL2651_SEL_ADDR_FLOAT << I2C_ID_MSB_BIT_MASK,reg);
} 

void tsl2651_write_register(uint16_t addy, uint8_t reg, uint8_t b) {
    i2c_device_write_reg(TSL2651_SEL_ADDR_FLOAT<< I2C_ID_MSB_BIT_MASK, reg, b);
}

uint16_t tsl2651_read_register16(uint16_t addy, uint16_t reg) {
return i2c_device_read_reg16(TSL2651_SEL_ADDR_FLOAT<< I2C_ID_MSB_BIT_MASK, reg);
} 

void tsl2651_write_register16(uint16_t addy, uint16_t reg, uint16_t b) {
    i2c_device_write_reg16(TSL2651_SEL_ADDR_FLOAT<< I2C_ID_MSB_BIT_MASK, reg, b);
}


