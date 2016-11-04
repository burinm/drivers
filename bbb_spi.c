#include "bbb_spi.h"
#include "../../../serbus/include/spidriver.h"

//This is mainly a library wrapper for 
// https://github.com/graycatlabs/serbus

static int spi_fd;

void spi_ss_low() {

}
void spi_ss_high() {

}

void spi_open_device(spi_mode_e m) {
spi_cpol_e cpol;
spi_cpha_e cpha;

    spi_set_cpol_cpha(&cpol, &cpha, m);

    SPI_setClockMode(spi_fd, m);
    SPI_setCSActiveLow(spi_fd);

    // /dev/spidev1.0
    spi_fd = SPI_open(1,0);
}

void spi_close_device() {
    // /dev/spidev1.0
    SPI_close(spi_fd);
}

void spi_set_bitorder(spi_bitorder_e o) {
    if (o == SPI_MSBit) { SPI_setBitOrder(spi_fd, SPI_MSBFIRST); }
    if (o == SPI_LSBit) { SPI_setBitOrder(spi_fd, SPI_LSBFIRST); }
}

void spi_start_transaction() {
    //nop in this library
}

void spi_stop_transaction() {
    //nop in this library

}

uint8_t spi_readwrite_byte(uint8_t b) {
uint8_t tx_buffer=b;
uint8_t rx_buffer=0;
    SPI_transfer(spi_fd,&tx_buffer,&rx_buffer, 1);

return rx_buffer;
}

void spi_read_byte() {
uint8_t rx_buffer=0;
    SPI_read(spi_fd, &rx_buffer, 1);

return rx_buffer;
}



