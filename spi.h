#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

#define SPI_CMD_DUMMY   0x0

typedef enum { SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3 } spi_mode_e;
typedef enum { CPOL0 = 0, CPOL1 = 1 } spi_cpol_e;
typedef enum { CPHA0 = 0, CPHA1 = 1 } spi_cpha_e;
typedef enum { SPI_LSBit = 0, SPI_MSBit = 1 } spi_bitorder_e;

static uint8_t SPI_GLOBAL_BITORDER=SPI_LSBit;

void spi_set_cpol_cpha(spi_cpol_e *cpol, spi_cpha_e *cpha, spi_mode_e m);
void spi_set_bitorder(spi_bitorder_e o);


#endif
