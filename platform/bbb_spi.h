/* bbb_spi.h

    BeagleBone Black SPI implementation

    Implements spi.h for the BBB 3.8.13-bone47
    with /lib/firmware/BB-SPIDEV0-00A0.dtbo

    This implementation uses the /dev/spidev1.0 device
    with one generic GPIO pin defined as follows:

    P9 header
        15 - gpio48                 /SS
        18 - /dev/spidev1.0         MOSI
        21 - /dev/spidev1.0         MISO
        22 - /dev/spidev1.0         CLK

    Right now this implementation is built on this driver:

    https://github.com/graycatlabs/serbus
        serbus/src/spidriver.c
            int SPI_open(uint8_t bus, uint8_t cs)
            int SPI_setClockMode(int spidev_fd, uint8_t clock_mode)
            int SPI_setMaxFrequency(int spidev_fd, uint32_t frequency)
            int SPI_setBitsPerWord(int spidev_fd, uint8_t bits_per_word)

    Setup:

    /media/burin/boot/uEnv.txt
        optargs=capemgr.disable_partno=BB-BONELT-HDMI,BB-BONELT-HDMIN
        optargs=quiet drm.debug=7 capemgr.enable_partno=BB-SPIDEV0

    chmod +x /etc/rc.local
    /etc/rc.local
        #P9 pin 15, set to GPIO
        echo 48 > /sys/class/gpio/export
        echo out > /sys/class/gpio/gpio48/direction
        echo 0 > /sys/class/gpio/gpio48/value

*/

#ifndef __BBB_SPI_H__
#define __BBB_SPI_H__

#include "../protocol/spi.h"

// Implements interface in spi.h 
void spi_ss_low();
void spi_ss_high();
void spi_open_device();
void spi_close_device();

void spi_start_transaction();
void spi_stop_transaction();

uint8_t spi_readwrite_byte(uint8_t b);
uint8_t spi_read_byte();

// End interface

#endif
