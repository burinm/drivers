/* bbb_i2c.c - (c) 2016 - burin */

#include "bbb_i2c.h"
#include <stdio.h>
#include <fcntl.h> //O_WRONLY
#include <unistd.h>

static int i2c_clk;
static int i2c_data_out;
static int i2c_data_in;

void i2c_open_device() {
    i2c_clk=open("/sys/class/gpio/gpio5/value",O_WRONLY);
    i2c_data_out=open("/sys/class/gpio/gpio4/value",O_WRONLY);
    i2c_data_in=open("/sys/class/gpio/gpio3/value",O_RDONLY);
}

void i2c_data_low() {
    write(i2c_data_out,"0",1);
}

void i2c_data_high() {
    write(i2c_data_out,"1",1);
}

void i2c_clock_low() {
    write(i2c_clk,"0",1);

}

void i2c_clock_high() {
    write(i2c_clk,"1",1);
}

i2c_level_e i2c_clock_read() {
uint8_t b=0;
    lseek(i2c_clk,0,SEEK_SET);
    read(i2c_clk,&b,1);
return (b == '1' ? 1 : 0);
}

i2c_level_e i2c_data_read() {
uint8_t b=0;
    lseek(i2c_data_in,0,SEEK_SET);
    read(i2c_data_in,&b,1);
return (b == '1' ? 1 : 0);

}
