#ifndef __PCF8574A_H__
#define __PCF8574A_H__

/* Driver for pcf8574a I/O expander
 *
 * This driver extends the i2c module
 *
 */

#include <stdint.h>

#define DEVICE_I2C_PCF8574A  0x7 //0111b

// Hardwired to A0,A1,A2 = 0 on the board
#define DEVICE_I2C_PCF8574A_ADDR 0x0 //000

typedef enum { DIR_IN, DIR_OUT } pcf8574a_io_direction_e;

void pcf8574a_open();

// Set pin to high/low
void pcf8574a_io_direction(uint8_t pin, pcf8574a_io_direction_e d); 
// Write 1 byte
void pcf8574a_write_port(uint8_t b);
// Read one byte
uint8_t pcf8574a_read_port();
// Set all ports to input
void pcf8574a_reset();

#endif
