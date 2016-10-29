#include "spi.h"

void spi_set_cpol_cpha(spi_cpol_e *cpol, spi_cpha_e *cpha, spi_mode_e m) {
    
/*
    CPOL=0 Active high, idle low
    CPOL=1 Active low, idle high

    CPHA=0 clock data on active->idle egde
    CPHA=1 clock data on idle->active edge (first edge)

*/
    switch(m) {
            case SPI_MODE0:
                *cpol=CPOL0; *cpha=CPHA0;
                break;
            case SPI_MODE1:
                *cpol=CPOL0; *cpha=CPHA1;
                break;
            case SPI_MODE2:
                *cpol=CPOL1; *cpha=CPHA0;
                break;
            case SPI_MODE3:
                *cpol=CPOL1; *cpha=CPHA1;
                break;
    }
}

void spi_set_bitorder(spi_bitorder_e o) {
    SPI_GLOBAL_BITORDER=o;
}
