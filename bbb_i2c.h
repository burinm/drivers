#ifndef __BBB_I2C_H__
#define __BBB_I2C_H__

#include "i2c.h"

/* BeagleBone Black SPI implementation

    Implements i2c.h for the BBB 3.8.13-bone47

    Mapped like this:
                                              SPI use
                                                    |
 /sys/kernel/debug/pinctrl/44e10800.pinmux/pins     |
                                             |      |
     offset   mode     BBB                   |      |
      0x15c   0x07     P9_17  gpio5          87     SCL 
      0x158   0x27     P9_18  gpio4          86     SDA 

    Setup:

    rc.local

    echo BITBANGI2C > /sys/devices/platform/bone_capemgr/slots
    echo 5 > /sys/class/gpio/export
    echo 4 > /sys/class/gpio/export
    echo out > /sys/class/gpio/gpio5/direction
    echo out > /sys/class/gpio/gpio4/direction
*/

// Implements interface in 12c.h
void i2c_open_device();

void i2c_data_low();
void i2c_data_high();

void i2c_clock_low();
void i2c_clock_high();

i2c_level_e i2c_clock_read();
i2c_level_e i2c_data_read();

void i2c_data_dir_in();
void i2c_data_dir_out();
// End implementation


#endif
