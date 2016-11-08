#include "spi.h"

spi_mode_e spi_mode=0;
spi_bitorder_e spi_bitorder=0;


void spi_set_cpol_cpha(spi_cpol_e *cpol, spi_cpha_e *cpha, spi_mode_e m) {
    
/*
    CPOL=0 clock active high, idle low
    CPOL=1 clock active low, idle high

    CPHA=0 clock data on idle->active edge (first edge)
    CPHA=1 clock data on active->idle egde

*/
    switch(m) {
            case SPI_MODE_0:
                *cpol=CPOL0; *cpha=CPHA0;
                break;
            case SPI_MODE_1:
                *cpol=CPOL0; *cpha=CPHA1;
                break;
            case SPI_MODE_2:
                *cpol=CPOL1; *cpha=CPHA0;
                break;
            case SPI_MODE_3:
                *cpol=CPOL1; *cpha=CPHA1;
                break;
    }
}

void spi_start_transaction() {
    spi_ss_low();
}

void spi_stop_transaction() {
    spi_ss_high();
}

void spi_set_mode(spi_mode_e m) {
    spi_mode = m;
}

void spi_set_bitorder(spi_bitorder_e o) {
    spi_bitorder = o;
}

