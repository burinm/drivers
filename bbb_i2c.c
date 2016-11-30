#include "bbb_i2c.h"

#include <stdio.h>
#include <fcntl.h> //O_WRONLY
#include <unistd.h>

static int i2c_clk;
static int i2c_data;
static int i2c_data_dir;

void i2c_open_device() {
    i2c_clk=open("/sys/class/gpio/gpio5/value",O_WRONLY);
    i2c_data=open("/sys/class/gpio/gpio4/value",O_RDWR);
    i2c_data_dir=open("/sys/class/gpio/gpio4/direction",O_WRONLY);
}

void i2c_data_low() {
    write(i2c_data,"0",1);
}

void i2c_data_high() {
    write(i2c_data,"1",1);
}

void i2c_data_dir_in() {
    write(i2c_data_dir,"in",2);
}

void i2c_data_dir_out() {
    write(i2c_data_dir,"out",3);
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
//i2c_data_dir_in();
    lseek(i2c_data,0,SEEK_SET);
    read(i2c_data,&b,1);
//i2c_data_dir_out();
return (b == '1' ? 1 : 0);

}

