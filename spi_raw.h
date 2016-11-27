#ifndef __SPI_RAW_H__
#define __SPI_RAW_H__

/* BeagleBone Black implementation of Bit Banged SPI driver

    Extends spi.h  bit banged interface

    Mapped like this:

                                              SPI use
                                                    |
 /sys/kernel/debug/pinctrl/44e10800.pinmux/pins     |
                                             |      |
     offset   mode     BBB                   |      |
       0x70    0x7     P9_11  gpio30         28     MOSI
       0x78    0x7     P9_12  gpio60         30     MISO
       0x74    0x7     P9_13  gpio31         29     CLK
       0x48    0x7     P9_14  gpio50         18     SS


    Setup:

    rc.local
        #This doesn't seem to work while kernel is booting:
        echo BITBANGSPI > /sys/devices/platform/bone_capemgr/slots
        echo 30 > /sys/class/gpio/export
        echo 60 > /sys/class/gpio/export
        echo 31 > /sys/class/gpio/export
        echo 50 > /sys/class/gpio/export
        echo out > /sys/class/gpio/gpio30/direction
        echo in > /sys/class/gpio/gpio60/direction
        echo out > /sys/class/gpio/gpio31/direction
        echo out > /sys/class/gpio/gpio50/direction
*/

#include "spi.h"

// Interface function implementation
void spi_ss_low();
void spi_ss_high();

void spi_mosi_low();
void spi_mosi_high();

extern uint8_t spi_miso_in();

void spi_clk_low();
void spi_clk_high();

void spi_open_device();
void spi_close_device();

void spi_start_transaction();
void spi_stop_transaction();

//end interface

#endif
