/* frdm_spi.h - (c) 2016 - burin

    SPI implementation for Freedom KL25Z development board

    Uses Native SPI , but ignores native /SS, SPI0_PCS0 (PTC4)
    Use GPIO PTC8 for /SS

    J1 header
        1  -        MISO
        9  -        CLK
        11 -        MOSI
        14 - PTC8   /SS
*/

#ifndef __FRDM_SPI_H__
#define __FRDM_SPI_H__

#include <stdint.h>
#include "spi.h"

// Implements interface in spi.h 
void spi_ss_low();
void spi_ss_high();
void spi_set_mode(spi_mode_e m);
void spi_open_device();
void spi_close_device();

void spi_set_bitorder(spi_bitorder_e o);

uint8_t spi_readwrite_byte(volatile uint8_t b);
uint8_t spi_read_byte();

//end interface


// Wait for transmit buffer to be ready for new data
void spi_wait_for_SPTEF();
// Is transmit buffer ready for new data  
uint8_t spi_is_SPTEF_set();

// Wait for data in the receive buffer
void spi_wait_for_SPRF();
// Is there data in the receive buffer
uint8_t spi_is_SPRF_set();

// Data in receive buffer is equal to match register
uint8_t spi_is_SPMF_set();

#endif
