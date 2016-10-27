#include "frdm_spi.h"
#include <MKL25Z4.h>

uint8_t spi_open_device(spi_cpol_e cpol, spi_cpha_e cpha) {

 SPI_C1_REG(SPI0) |= SPI_C1_SPE_MASK |                    // SPI system enable
             SPI_C1_MSTR_MASK |                               // SPI master
             ((cpol == CPOL_IDLE_HIGH)  & SPI_C1_CPOL_MASK) | // Active Low
             ((cpha == CPHA_EDGE) & SPI_C1_CPHA_MASK);   // clock at start of cycle
                         

SPI_BR_REG(SPI0) |= (0x1 & SPI_BR_SPR_MASK);//  prescaler=1, divisor=4
//                   That is 24MHz/4 = 6MHz

// Setup GPIO pin for ss
PORTC_PCR8 = PORT_PCR_MUX(1); // Port C8 to GPIO
PTC_BASE_PTR->PDDR |= 1<<8;   // Set port C, pin 18 data direction to output
}

void spi_ss_low() {
    PTC_BASE_PTR->PCOR |= 1<<8;
}

void spi_ss_high() {
    PTC_BASE_PTR->PSOR |= 1<<8;
}

void spi_send_byte(uint8_t b) {

spi_ss_low();
//Read S, while SPTEF == 1
while( !(SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK)); 

//Write byte
SPI_D_REG(SPI0) = b;
spi_ss_high();

}
