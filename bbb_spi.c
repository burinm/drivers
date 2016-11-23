#include "bbb_spi.h"
#include "../../../serbus/include/spidriver.h"

//open file...
#include <stdio.h>
#include <fcntl.h> //O_WRONLY



#include "util.h" //logging remove later

//This is mainly a library wrapper for 
// https://github.com/graycatlabs/serbus

static int spi_fd;
static int spi_gpio_fd;

void spi_ss_low() {
    write(spi_gpio_fd,"0",1);
    //echo 0 > /sys/class/gpio/gpio48/value
}

void spi_ss_high() {
    write(spi_gpio_fd,"1",1);
    //echo 0 > /sys/class/gpio/gpio48/value
}

void spi_open_device() {
int8_t error=0;

    //Setup GPIO pin interface
    spi_gpio_fd=open("/sys/class/gpio/gpio48/value",O_WRONLY);
    spi_ss_high();

    // /dev/spidev1.0
    spi_fd = SPI_open(1,0);

    error = SPI_setClockMode(spi_fd, (uint8_t)spi_mode);
    if (error == -1 ) { LOG0("couldn't set clock mode\n"); }
    error = 0;
    error = SPI_setMaxFrequency(spi_fd,1000000);
    if (error == -1 ) { LOG0("couldn't set frequency\n"); }
    error = 0;
    error = SPI_setBitsPerWord(spi_fd,8);
    if (error == -1 ) { LOG0("couldn't set bits per word\n"); }
    // We are going to drive our own CS from a GPIO pin
    //if (SPI_disableCS(spi_fd) == -1) { LOG0("couldn't set CS"); }
SPI_setBitOrder(spi_fd, spi_bitorder);

}

void spi_close_device() {
    // /dev/spidev1.0
    SPI_close(spi_fd);
    close(spi_gpio_fd);
}

uint8_t spi_readwrite_byte(uint8_t b) {
uint8_t tx_buffer=b;
uint8_t rx_buffer=0;
    SPI_transfer(spi_fd,&tx_buffer,&rx_buffer, 1);

return rx_buffer;
}

uint8_t spi_read_byte() {
uint8_t rx_buffer=0;
    SPI_read(spi_fd, &rx_buffer, 1);

return rx_buffer;
}
