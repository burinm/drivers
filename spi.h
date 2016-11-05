#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

//Interface, these must be implemented by platform
#define SPI_CMD_DUMMY   0x0

typedef enum { SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3 } spi_mode_e;
typedef enum { CPOL0 = 0, CPOL1 = 1 } spi_cpol_e;
typedef enum { CPHA0 = 0, CPHA1 = 1 } spi_cpha_e;
typedef enum { SPI_LSBit = 0, SPI_MSBit = 1 } spi_bitorder_e;

extern void spi_ss_low();
extern void spi_ss_high();
void spi_set_mode(spi_mode_e m);
extern void spi_open_device();
extern void spi_close_device();

extern void spi_set_bitorder(spi_bitorder_e o);

extern uint8_t spi_readwrite_byte(uint8_t b);
extern uint8_t spi_read_byte();

//End interface

//static uint8_t SPI_GLOBAL_BITORDER=SPI_LSBit;
void spi_start_transaction();
void spi_stop_transaction();


void spi_set_cpol_cpha(spi_cpol_e *cpol, spi_cpha_e *cpha, spi_mode_e m);


#endif
