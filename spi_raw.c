#include "spi_raw.h"

#include <stdio.h>
#include <fcntl.h> //O_WRONLY
#include <unistd.h>


#include "util.h" //logging remove later




static int spi_gpio_mosi;
static int spi_gpio_miso;
static int spi_gpio_clk;
static int spi_gpio_ss;


void spi_open_device() {

    //Setup GPIO pin interface
    spi_gpio_mosi=open("/sys/class/gpio/gpio30/value",O_WRONLY);
    spi_gpio_miso=open("/sys/class/gpio/gpio60/value",O_RDONLY);
    spi_gpio_clk=open("/sys/class/gpio/gpio31/value",O_WRONLY);
    spi_gpio_ss=open("/sys/class/gpio/gpio50/value",O_WRONLY);

    spi_ss_high();


    // Set clock Mode
    // Set Frequency
    // Set bits per word
    // Set bit order

    // For first cut, SPI Mode 0 only

}

void spi_close_device() {
    close(spi_gpio_ss);
    close(spi_gpio_clk);
    close(spi_gpio_miso);
    close(spi_gpio_mosi);
}

void spi_ss_low() {
    write(spi_gpio_ss,"0",1);
}

void spi_ss_high() {
    write(spi_gpio_ss,"1",1);
}

void spi_mosi_low() {
    write(spi_gpio_mosi,"0",1);
}

void spi_mosi_high() {
    write(spi_gpio_mosi,"1",1);
}

uint8_t spi_miso_in() {
uint8_t b=0;
    lseek(spi_gpio_miso,0,SEEK_SET);
    read(spi_gpio_miso,&b,1);
return (b == '1' ? 1 : 0); 
}

void spi_clk_low() {
    write(spi_gpio_clk,"0",1);
}

void spi_clk_high() {
    write(spi_gpio_clk,"1",1);
}
