#include "frdm_spi.h"
#include "frdm_firmware.h"
#include "kl25z.arch/MKL25Z4.h"

void spi_open_device(spi_mode_e m) {
uint8_t b=0;

spi_cpol_e cpol;
spi_cpha_e cpha;
spi_set_cpol_cpha(&cpol, &cpha, m);


// Turn on port C
SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
// Set up ports for SPI0
PORTC->PCR[4] |= PORT_PCR_MUX(2);
PORTC->PCR[5] |= PORT_PCR_MUX(2);
PORTC->PCR[6] |= PORT_PCR_MUX(2);
PORTC->PCR[7] |= PORT_PCR_MUX(2);
// Set up ss pin as GPIO
//  Setup port C, pin 8 GPIO for ss line
PORTC->PCR[8] |= PORT_PCR_MUX(1);
// Set port C, pin 8 data direction to output
PTC_BASE_PTR->PDDR |= 1<<8;

// Turn on SPI0 clock
SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;


SPI_C1_REG(SPI0) |= SPI_C1_SPE_MASK |               // SPI system enable
             SPI_C1_MSTR_MASK |                     // SPI master
             ((cpol == CPOL1) & SPI_C1_CPOL_MASK) | // Active Low, defaule High
             ((cpha == CPHA1) & SPI_C1_CPHA_MASK);  // clock idle-> active
                         
// prescaler=1, divisor=4 , 24MHz/4 = 6MHz
SPI_BR_REG(SPI0) |= (0x1 & SPI_BR_SPR_MASK);

// prescaler=1, divisor=512, 24MHZ/512  = 46875Hz
//SPI_BR_REG(SPI0) |= (0x3 & SPI_BR_SPR_MASK);
//                   That is 24MHz/4 = 6MHz


GPIOC->PDDR |= 1<<8;

//Initialization dance
// KL25 Sub-Family Reference manual p686
do { 
spi_wait_for_SPTEF();

//Write dummy byte
SPI_D_REG(SPI0) = 0x0;
spi_wait_for_SPTEF();
spi_wait_for_SPTEF();

//TODO: make sure this doesn't get optimized out
b=SPI_D_REG(SPI0);
} while ( !spi_is_SPTEF_set());

//Read SPMF while set to clear flag
//TODO: make sure this doesn't get optimized out
b=SPI_D_REG(SPI0);
SPI_D_REG(SPI0) |= SPI_S_SPTEF_MASK;


}

void spi_ss_low() {
    PTC_BASE_PTR->PCOR |= 1<<8;
}

void spi_ss_high() {
    PTC_BASE_PTR->PSOR |= 1<<8;
}

void spi_send_byte(uint8_t b) {

spi_ss_low();
FRDM_WAIT_8
//Read S, while SPTEF == 1
spi_wait_for_SPTEF();

//Write byte
SPI_D_REG(SPI0) = b;
FRDM_WAIT_8
FRDM_WAIT_8
FRDM_WAIT_8
FRDM_WAIT_8
FRDM_WAIT_8
FRDM_WAIT_8
FRDM_WAIT_8
FRDM_WAIT_8
FRDM_WAIT_8
FRDM_WAIT_8
spi_ss_high();

}

void spi_read_byte() {
uint8_t b;

b = SPI_D_REG(SPI0);

}

void spi_wait_for_SPTEF() {
    while( (SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK) == 0) {
        __asm__("nop;");
    }
}

uint8_t spi_is_SPTEF_set() {
    return (SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK);
}
