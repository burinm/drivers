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

void spi_start_transaction(void) {
    spi_ss_low();
}

void spi_stop_transaction(void) {
    spi_ss_high();
}

void spi_set_mode(spi_mode_e m) {
    spi_mode = m;
}

void spi_set_bitorder(spi_bitorder_e o) {
    spi_bitorder = o;
}

#ifndef FRDM_KL25Z
uint8_t spi_readwrite_byte(uint8_t b) {
uint8_t i;
uint8_t out;

    out=0;
    for (i=0;i<8;i++) {
        b & 0x80 ? spi_mosi_high() : spi_mosi_low();
        b=b<<1;
        
        spi_clk_high();
    
        if (spi_miso_in()) { out |= 0x1; }

        if (i<7) { out<<=1; }
        spi_clk_low();
    }
    

return out;
}
#endif

#if 0
uint8_t spi_read_byte() {
uint8_t out;

return out;
}
#endif

