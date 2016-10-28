#ifndef __FRDM_SPI_H__
#define __FRDM_SPI_H__

#include <stdint.h>
#include "spi.h"

void spi_ss_low();
void spi_ss_high();
void spi_open_device(spi_mode_e m);
void spi_send_byte(uint8_t b);
void spi_read_byte();

void spi_wait_for_SPTEF();
uint8_t spi_is_SPTEF_set();

#endif
