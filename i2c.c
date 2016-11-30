#include "i2c.h"
#include <stdio.h>

//remember to inline all of this

void i2c_open() {
    i2c_open_device();
    i2c_idle();
}

void i2c_reset() {
uint8_t i;

//Better would be to wait for data - high?
//This is my guess at a reset routine
    for (i=0;i<8;i++) {
        i2c_clock_low();
I2C_DELAY
        i2c_clock_high();
I2C_DELAY
    }

    i2c_clock_low();
I2C_DELAY
    i2c_idle(); 
}

void i2c_mem_device_reset() {
uint8_t i;

    i2c_start();

    i2c_data_high();
    for (i=0;i<9;i++) {
        i2c_one_clock();
I2C_DELAY
    }

    i2c_clock_low();
    i2c_data_low();

    i2c_start();
    i2c_stop();
I2C_DELAY
    i2c_idle(); 
}

void i2c_set_device_id(uint8_t d) {
    i2c_device_id=d;
}

void i2c_set_page_size(uint8_t s) {
    i2c_page_size=s;
}

void i2c_idle() {
        i2c_clock_high();
        i2c_data_high();
}

uint8_t i2c_is_idle() {

return ( (i2c_clock_read()  == HIGH ) && (i2c_data_read() == HIGH));

}

void i2c_start() {
        i2c_data_high();
I2C_DELAY //Setup time is 600ns
        i2c_clock_high();
        i2c_data_low();
I2C_DELAY
        i2c_clock_low();
}

void i2c_stop() { 
        i2c_data_low();
I2C_DELAY //Setup time is 600ns
        i2c_clock_high();
I2C_DELAY
        i2c_data_high();
       // i2c_clock_low();
I2C_DELAY
//        i2c_idle();
}

void i2c_send_databit(i2c_level_e d) {
        i2c_clock_low();
        (d == HIGH) ? i2c_data_high() : i2c_data_low();
I2C_DELAY //Setup time is 100ns, so this is generous
        i2c_clock_high();
I2C_DELAY
        i2c_clock_low();
I2C_DELAY //900ns Output valid from clock

}

i2c_level_e i2c_get_databit() {
i2c_level_e b;
        i2c_clock_low();
        i2c_clock_high();
I2C_DELAY
        b = i2c_data_read();
        i2c_clock_low();
I2C_DELAY
return b;
}

uint8_t i2c_ack_acknowledge() {
uint8_t ack=0;

        i2c_data_high();
        i2c_clock_high();
//Wait for slave to ack by pulling data low
I2C_DELAY
        if (i2c_data_read() == LOW) { ack = 1; }
        i2c_clock_low();

return ack;
}

void i2c_one_clock() {
    i2c_clock_high();
I2C_DELAY
    i2c_clock_low();
}

uint8_t i2c_did_slave_ack() {
    return (i2c_data_read() == LOW);
}

void i2c_wait_for_data_low() {
//TODO timeout logic
        while(i2c_data_read() == HIGH);
}

void i2c_ack_poll(uint16_t addy) {
    do {
        i2c_start();
        i2c_send_control_byte( ((addy & I2C_MSB_MASK) >> I2C_LSB_BITS) , WRITE);
    } while (! i2c_ack_acknowledge() );
}

void i2c_send_byte(uint8_t b) {
uint8_t i=0;

    for (i=0;i<I2C_LSB_BITS;i++) {
        i2c_send_databit( (b & I2C_LSB_BIT_MASK) ? HIGH:LOW);
        b <<=1; //MSB first
    }

    i2c_data_high(); //To avoid false NACKs

}

uint8_t i2c_get_byte() {
uint8_t i=0;
uint8_t b=0;

    for (i=0;i<7;i++) {
        b |= ( (i2c_get_databit() == HIGH) ? 1:0);
        b <<=1;
    }
    b |= ( (i2c_get_databit() == HIGH) ? 1:0);
return b;
}

void i2c_send_control_byte(uint8_t msb_addy ,i2c_action_e a) {
    uint8_t i=0;
    uint8_t d_id= i2c_device_id & I2C_ID_MASK;

    // Send device id, 4 bits
    for (i=0;i<I2C_ID_BITS;i++) {
        i2c_send_databit( (d_id & I2C_ID_MSB_BIT_MASK) ? HIGH:LOW);
        d_id <<=1; //MSB first
    }
    // Send MSBit address, 3 bits
    for (i=0;i<I2C_MSB_BITS;i++) {
        i2c_send_databit( (msb_addy & I2C_MSB_BIT_MASK) ? HIGH:LOW);
        msb_addy <<=1; //MSB first
    }

    // Send read/write, 1 bit
    i2c_send_databit( (a == READ) ? HIGH:LOW);
}

void i2c_device_write_byte(uint16_t addy, uint8_t b) {
    i2c_start();

    i2c_prot_setup_read_write(addy, WRITE);
    i2c_ack_acknowledge();

    i2c_send_byte( (addy & I2C_LSB_MASK) );
    i2c_ack_acknowledge();

    i2c_send_byte(b);
    i2c_ack_acknowledge();
    i2c_stop();
    i2c_ack_poll(addy);
    i2c_stop();
}

void i2c_device_simple_write_byte(int16_t addy, uint8_t b) {
    i2c_start();

    i2c_prot_setup_read_write(addy, WRITE);
    i2c_ack_acknowledge();

    i2c_send_byte(b);
    i2c_ack_acknowledge();

    i2c_stop();
    i2c_ack_poll(addy);
    i2c_stop();
}

void i2c_prot_setup_read_write(uint16_t addy, i2c_action_e rw) {

    i2c_send_control_byte( ((addy & I2C_MSB_MASK) >> I2C_LSB_BITS),
                            (rw == READ) ? HIGH:LOW );
}

uint8_t i2c_device_read_random_byte(uint16_t addy) {
uint8_t b;
    i2c_start();
    i2c_prot_setup_read_write(addy, WRITE);
    i2c_ack_acknowledge();

    i2c_send_byte( (addy & I2C_LSB_MASK) );
    i2c_ack_acknowledge();

    i2c_start();

    i2c_prot_setup_read_write(addy, READ);
    i2c_ack_acknowledge();

    b =i2c_get_byte();
        //NACK
        i2c_data_high();
I2C_DELAY //setup time = ??
        i2c_clock_low();
        i2c_clock_high();
I2C_DELAY
        i2c_clock_low();
        //End NACK
    i2c_stop();
return b;
}

uint8_t i2c_device_simple_read_byte(uint16_t addy) {
uint8_t b;
    i2c_start();
    i2c_prot_setup_read_write(addy, READ);
    i2c_ack_acknowledge();

    b =i2c_get_byte();
        //NACK
        i2c_data_high();
I2C_DELAY //setup time = ??
        i2c_clock_low();
        i2c_clock_high();
I2C_DELAY
        i2c_clock_low();
        //End NACK
    i2c_stop();
return b;
}

void i2c_device_write_block(uint16_t addy, uint8_t b, size_t s) {
    _i2c_device_write_bytes(addy, &b, s, 1);
}

void i2c_device_write_bytes(uint16_t addy, uint8_t *b, size_t s) {
    _i2c_device_write_bytes(addy, b, s, 0);
}

void _i2c_device_write_bytes(uint16_t addy, uint8_t *b, size_t s, uint8_t fill) {
size_t i=0;
uint8_t j=0;

while (s) {
    //Setup for write
    i2c_start();
    i2c_prot_setup_read_write(addy, WRITE);
    i2c_ack_acknowledge();
    //Send lsb of address, 8 bits
    i2c_send_byte( (addy & I2C_LSB_MASK) );
    i2c_ack_acknowledge();

    for(j=addy%i2c_page_size;j<i2c_page_size;j++) {
        i2c_send_byte(*b);
        i2c_ack_acknowledge();
        addy++;
        s--;
        if (!fill) { b++; }
        if (s == 0) { break; } 
    }
    i2c_stop();
    i2c_ack_poll(addy);
    i2c_stop();
I2C_DELAY
}

}


#if 0
void i2c_device_read_current_byte(uint16_t addy, uint8_t b) {

}

void i2c_device_read_random(uint16_t addy, uint8_t b) {

}

void i2c_device_read_sequential(uint16_t addy, uint8_t b) {

}
#endif
