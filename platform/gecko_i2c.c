/* gecko_i2c.c - (c) 2017 - burin */

#include "gecko_i2c.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"

void i2c_open_device() {
uint8_t i=0;

    CMU_ClockEnable(cmuClock_GPIO, true);

    GPIO_PinModeSet(GECKO_I2C_SDA_PORT, GECKO_I2C_SDA_PORT_NUM,
                        gpioModeWiredAnd, 1);
    GPIO_PinModeSet(GECKO_I2C_SCL_PORT, GECKO_I2C_SCL_PORT_NUM,
                        gpioModeWiredAnd, 1);

//Reset any devices on line 
for (i=0;i<9;i++) {
    GPIO_PinModeSet(GECKO_I2C_SCL_PORT, GECKO_I2C_SCL_PORT_NUM,
                        gpioModeWiredAnd, 0);
    GPIO_PinModeSet(GECKO_I2C_SCL_PORT, GECKO_I2C_SCL_PORT_NUM,
                        gpioModeWiredAnd, 1);
}
    GPIO_PinModeSet(GECKO_I2C_SCL_PORT, GECKO_I2C_SCL_PORT_NUM,
                        gpioModeWiredAnd, 0);

//I2C bus IDLE
    GPIO_PinModeSet(GECKO_I2C_SDA_PORT, GECKO_I2C_SDA_PORT_NUM,
                        gpioModeWiredAnd, 1);
    GPIO_PinModeSet(GECKO_I2C_SCL_PORT, GECKO_I2C_SCL_PORT_NUM,
                        gpioModeWiredAnd, 1);

//I2c on
    CMU_ClockEnable(cmuClock_I2C1, true);
    // Select pins PC5,PC4 alternative I2C functionality, turn on SDA,SCL
    I2C1->ROUTE = (_I2C_ROUTE_LOCATION_LOC0 << _I2C_ROUTE_LOCATION_SHIFT) |
            I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;

    const I2C_Init_TypeDef i2c_init = {
            .enable = true,                  /* Enable when init done */ 
            .master = true,                  /* Set to master mode */ 
            .refFreq = 0,                    /* Use currently configured reference clock */
            .freq = I2C_FREQ_STANDARD_MAX,   /* Set to standard rate assuring being */ 
            //.freq = 40000,                 /* Slower test frequency for my logic analyzer */
            .clhr = i2cClockHLRStandard      /* Set to use 4:4 low/high duty cycle */
    };

    I2C_Init(I2C1, &i2c_init);
}

void i2c_close_device() {
    GPIO_PinModeSet(GECKO_I2C_SDA_PORT, GECKO_I2C_SDA_PORT_NUM,
                        gpioModeDisabled, 0);
    GPIO_PinModeSet(GECKO_I2C_SCL_PORT, GECKO_I2C_SCL_PORT_NUM,
                        gpioModeDisabled, 0);
}

// Hardware specific
uint8_t i2c_busy() {
return (I2C1->STATE & I2C_STATE_BUSY);
}

void i2c_abort() {
    I2C1->CMD = I2C_CMD_ABORT;
}

void i2c_cmd_start() {
    I2C1->CMD = I2C_CMD_START;
}

void i2c_cmd_stop() {
    I2C1->CMD = I2C_CMD_STOP;
}

void i2c_cmd_ack() {
    I2C1->CMD = I2C_CMD_ACK;
}

void i2c_cmd_nack() {
    I2C1->CMD = I2C_CMD_NACK;
}

void i2c_set_txdata(uint8_t tx) {
    I2C1->TXDATA = tx; 
}

uint8_t i2c_is_ack() {
return ((I2C1->IF & I2C_IF_ACK));
}

void i2c_clear_ack() {
    I2C1->IFC = I2C_IFC_ACK;
}

uint8_t i2c_get_rxdata() {
    while((I2C1->IF & I2C_IF_RXDATAV) ==0);
return (I2C1->RXDATA);
}

// Unused in this implementation
#if 0
void i2c_data_low() {
}

void i2c_data_high() {
}

void i2c_clock_low() {
}

void i2c_clock_high() {
}

i2c_level_e i2c_clock_read() {
return LOW;
}

i2c_level_e i2c_data_read() {
return LOW;
}
#endif
