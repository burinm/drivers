#ifndef __SPI_RAW_H__
#define __SPI_RAW_H__

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
