/* sbc_spi.h - (c) 2016 - burin

    65c02 Single Board Computer SPI driver implementation 

    implements spi.h

    memory mapped 65c22 I/O expander GPIO SPI driver

    Mapped as follows:

    PortB on VIA at 0x8010

    SBC_PIN_MOSI    PB6
    SBC_PIN_MISO    PB7
    SBC_PIN_CLK     PB0
    SBC_PIN_SS      PB1
*/
 
#ifndef __SBC_SPI_H__
#define __SBC_SPI_H__

#include <stdint.h>

#define VIA_0 (uint8_t*)(0x8010)
#define VIA_1 (uint8_t*)(0x8020)

//SPI interface pins (using port B)
#define SBC_PIN_MOSI    6
#define SBC_PIN_MISO    7
#define SBC_PIN_CLK     0
#define SBC_PIN_SS      1

// Implements interface spi.h
void spi_ss_low(void);
void spi_ss_high(void);
void spi_open_device(void);
void spi_close_device(void);
void spi_mosi_low(void);
void spi_mosi_high(void);
uint8_t spi_miso_in(void);
void spi_clk_low(void);
void spi_clk_high(void);
// End interface

#endif
