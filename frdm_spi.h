#ifndef __FRDM_SPI_H__
#define __FRDM_SPI_H__

#include <stdint.h>
#include "spi.h"

void spi_ss_low();
void spi_ss_high();
uint8_t spi_open_device(spi_cpol_e cpol, spi_cpha_e cpha);
void spi_send_byte(uint8_t b);

#endif
