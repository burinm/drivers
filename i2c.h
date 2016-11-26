#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>
#include <stddef.h> //size_t

static uint8_t i2c_device_id;
static uint8_t i2c_page_size;

//Interface, these must be implemented by platform
typedef enum { LOW=0, HIGH=1 } i2c_level_e;
typedef enum { WRITE=0, READ=1 } i2c_action_e;

// Connect to actual hardware, GPIO pins, etc
extern void i2c_open_device();

// Bring hardware data pin low/high
extern void i2c_data_low();
extern void i2c_data_high();

// Bring hardware clock pin low/high
extern void i2c_clock_low();
extern void i2c_clock_high();

// Hardware read clock/data pins
extern i2c_level_e i2c_clock_read();
extern i2c_level_e i2c_data_read();

//End interface

//This may have to be adjusted for a fater system
// right now it does nothing
#define I2C_DELAY

// Two wire I2C protocol implementation

#define I2C_ID_MASK         0xf
#define I2C_ID_BITS         4 
#define I2C_ID_MSB_BIT_MASK 0x8 

// i2c addressing masks
#define I2C_MSB_MASK        0x0700
#define I2C_MSB_BITS        3 
#define I2C_MSB_BIT_MASK    0x4

#define I2C_LSB_MASK        0xff
#define I2C_LSB_BITS        8 
#define I2C_LSB_BIT_MASK    0x80


//My homegrown reset
void i2c_reset();

//AN709 official memory reset
void i2c_mem_device_reset();

// Idle. Clock high, data high
void i2c_idle();

uint8_t i2c_is_idle(); // 0= busy, 1=idle
void i2c_start(); // Send start sequence
void i2c_stop();  // Send stop sequence
void i2c_send_databit(i2c_level_e); // Send data bit
i2c_level_e i2c_get_databit(); // Get data bit
uint8_t i2c_ack_acknowledge(); // Master reply to slave ack 
uint8_t i2c_did_slave_ack(); // Did slave pull data low? 
void i2c_wait_for_data_low(); // Wait for slave to pull line low

// Ack polling for write. (blocking)
void i2c_ack_poll(uint16_t addy);

// Good for 9th bit if not ACK polling
void i2c_one_clock();

// Master start transaction, read or write
void i2c_send_control_byte(uint8_t msb_addy ,i2c_action_e a);

// Master send byte
void i2c_send_byte(uint8_t b);

// Master get byte
uint8_t i2c_get_byte();

//Protocol sequences (i.e. more than setting states)

// Send control byte, specify read/write
void i2c_prot_setup_read_write(uint16_t addy, i2c_action_e rw);

//Device level APIs
// Use these to construct device drivers for I2C devices

// Initialization
void i2c_open();

// The device must call these setup functions
//TODO: this needs to be reworked - model is wrong
//  for multiple devices
void i2c_set_device_id(uint8_t d);
void i2c_set_page_size(uint8_t d);

// Write functions

//i2c write one byte
void i2c_device_write_byte(uint16_t addy, uint8_t b);

//i2c write byte, 7 bit address only
void i2c_device_simple_write_byte(int16_t addy, uint8_t b);

// i2c page write
void i2c_device_write_bytes(uint16_t addy, uint8_t *b, size_t s);

// page write the same one byte of data ( i.e. erase b=0x0 )
void i2c_device_write_block(uint16_t addy, uint8_t b, size_t s);

// ic2 read random byte
uint8_t i2c_device_read_random_byte(uint16_t addy);

// i2c read byte, 7 bit address only
uint8_t i2c_device_simple_read_byte(uint16_t addy);

// Currently not implemented
#if 0
void i2c_device_read_current_byte(uint16_t addy, uint8_t b);
void i2c_device_read_random(uint16_t addy, uint8_t b);
void i2c_device_read_sequential(uint16_t addy, uint8_t b);
#endif

// Actual write routine, private
void _i2c_device_write_bytes(uint16_t addy, uint8_t *b, size_t s, uint8_t fill);

#endif
