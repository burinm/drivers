#ifndef __BBB_SPI_H__
#define __BBB_SPI_H__

#include "spi.h"

// Interface function implementation
void spi_ss_low();
void spi_ss_high();
void spi_open_device();
void spi_close_device();

void spi_start_transaction();
void spi_stop_transaction();

uint8_t spi_readwrite_byte(uint8_t b);
uint8_t spi_read_byte();

//end interface

#endif
