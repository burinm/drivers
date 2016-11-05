#ifndef __FRDM_SPI_H__
#define __FRDM_SPI_H__

#include <stdint.h>
#include "spi.h"

// Interface function implementation
void spi_ss_low();
void spi_ss_high();
void spi_set_mode(spi_mode_e m);
void spi_open_device();
void spi_close_device();

void spi_set_bitorder(spi_bitorder_e o);

uint8_t spi_readwrite_byte(uint8_t b);
void spi_read_byte();

//end interface

void spi_wait_for_SPTEF();
uint8_t spi_is_SPTEF_set();

void spi_wait_for_SPRF();
uint8_t spi_is_SPRF_set();

uint8_t spi_is_SPMF_set();

#endif
