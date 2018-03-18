/* sbc_spi.c - (c) 2016 - burin */

#include "sbc_spi.h"
#include "6522.h"

void spi_open_device(void) {
    // Set up pin directions for port B
    DEVICE_6522_SET_DDB_OUT(VIA_0,SBC_PIN_MOSI);
    DEVICE_6522_SET_DDB_IN(VIA_0,SBC_PIN_MISO);
    DEVICE_6522_SET_DDB_OUT(VIA_0,SBC_PIN_CLK);
    DEVICE_6522_SET_DDB_OUT(VIA_0,SBC_PIN_SS);

    // /SS High, all other pins low
    spi_ss_high();
    spi_mosi_low();
    spi_clk_low();
}

void spi_close_device(void) {
    //nop
}

void spi_ss_low(void) {
    DEVICE_6522_WRITE_B(VIA_0,DEVICE_6522_READ_B(VIA_0) & ~(1<<SBC_PIN_SS));
}

void spi_ss_high(void) {
    DEVICE_6522_WRITE_B(VIA_0,DEVICE_6522_READ_B(VIA_0) | 1<<SBC_PIN_SS);
}

void spi_mosi_low(void) {
    DEVICE_6522_WRITE_B(VIA_0,DEVICE_6522_READ_B(VIA_0) & ~(1<<SBC_PIN_MOSI));
}

void spi_mosi_high(void) {
    DEVICE_6522_WRITE_B(VIA_0,DEVICE_6522_READ_B(VIA_0) | 1<<SBC_PIN_MOSI);
}

uint8_t spi_miso_in(void) {
    return ( !!(1<<SBC_PIN_MISO & DEVICE_6522_READ_B(VIA_0)));
}

void spi_clk_low(void) {
    DEVICE_6522_WRITE_B(VIA_0,DEVICE_6522_READ_B(VIA_0) & ~(1<<SBC_PIN_CLK));
}

void spi_clk_high(void) {
    DEVICE_6522_WRITE_B(VIA_0,DEVICE_6522_READ_B(VIA_0) | 1<<SBC_PIN_CLK);
}
