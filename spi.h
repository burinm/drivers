#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

#define SPI_CMD_DUMMY   0x0

typedef enum { SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3 } spi_mode_e;
typedef enum { CPOL0 = 0, CPOL1 = 1 } spi_cpol_e;
typedef enum { CPHA0 = 0, CPHA1 = 1 } spi_cpha_e;
typedef enum { SPI_LSBit = 0, SPI_MSBit = 1 } spi_bitorder_e;

//Interface, these must be implemented by platform

// Pull the /SS line low
extern void spi_ss_low();

// Pull the /SS line high 
extern void spi_ss_high();

// open and close setup for specific device 
extern void spi_open_device();
extern void spi_close_device();

// platform specific read/write - Only for plaforms with native SPI silicon
extern uint8_t spi_readwrite_byte(uint8_t b);
//extern uint8_t spi_read_byte();


// additional interface for bit banged platforms

// Pull the MOSI line low/high
extern void spi_mosi_low();
extern void spi_mosi_high();

// read MISO line
extern uint8_t spi_miso_in();

// Pull the CLK line low/high
extern void spi_clk_low();
extern void spi_clk_high();


//End interface

spi_mode_e spi_mode;
spi_bitorder_e spi_bitorder;

// These set global flags that can be used in spi_open_device
void spi_set_mode(spi_mode_e m);
void spi_set_bitorder(spi_bitorder_e o);

// These are used for start/stop SPI transaction
void spi_start_transaction();
void spi_stop_transaction();


// Translates SPI Mode into CPOL and CPHA flags
void spi_set_cpol_cpha(spi_cpol_e *cpol, spi_cpha_e *cpha, spi_mode_e m);

// SPI read and write byte
uint8_t spi_readwrite_byte(uint8_t b);
uint8_t spi_read_byte();



#endif
