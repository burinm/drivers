#include "frdm_spi.h"
#include "frdm_firmware.h"
#include "kl25z.arch/MKL25Z4.h"

void spi_open_device(spi_mode_e m) {
spi_cpol_e cpol;
spi_cpha_e cpha;


// Turn on port C
SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
// Set up ports for SPI0
PORTC->PCR[8] |= PORT_PCR_MUX(1); // ss as gpio pin
PORTC->PCR[5] |= PORT_PCR_MUX(2);
PORTC->PCR[6] |= PORT_PCR_MUX(2);
PORTC->PCR[7] |= PORT_PCR_MUX(2);

// Set port C, pin 8 data direction to output
PTC_BASE_PTR->PDDR |= 1<<8;

// Turn on SPI0 clock
SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;


spi_set_cpol_cpha(&cpol, &cpha, m);
SPI_C1_REG(SPI0) |= SPI_C1_SPE_MASK |               // SPI system enable
             SPI_C1_MSTR_MASK |                     // SPI master
             ((cpol == CPOL1) & SPI_C1_CPOL_MASK) | // Active Low, defaule High
             ((cpha == CPHA1) & SPI_C1_CPHA_MASK);  // clock idle-> active
                         
// prescaler=1, divisor=4 , 24MHz/4 = 6MHz
SPI_BR_REG(SPI0) |= (0x1 & SPI_BR_SPR_MASK);

spi_ss_high();

//Initialization dance
// KL25 Sub-Family Reference manual p686
do { 
spi_wait_for_SPTEF();

//Write dummy byte
SPI_D_REG(SPI0) = SPI_CMD_DUMMY;

spi_wait_for_SPRF();

//TODO: make sure this doesn't get optimized out
(void)SPI_D_REG(SPI0);
} while ( !spi_is_SPMF_set());

//Read SPMF while set to clear flag
//TODO: make sure this doesn't get optimized out
(void)SPI_D_REG(SPI0);
SPI_D_REG(SPI0) |= SPI_S_SPMF_MASK;

//I think we need an initial read/write
//spi_readwrite_byte(SPI_CMD_DUMMY);
//SPI_D_REG(SPI0) = SPI_CMD_DUMMY;
//b=SPI_D_REG(SPI0);

}

void spi_ss_low() {
    PTC_BASE_PTR->PCOR |= 1<<8;
}

void spi_ss_high() {
    PTC_BASE_PTR->PSOR |= 1<<8;
}

void spi_start_transaction() {
    spi_ss_low();
}

void spi_stop_transaction() {
    spi_ss_high();
}


uint8_t spi_readwrite_byte(uint8_t b) {

spi_wait_for_SPTEF();

SPI_D_REG(SPI0) = b;
spi_wait_for_SPRF();
b=SPI_D_REG(SPI0);

return b;
}

void spi_read_byte() {

(void)SPI_D_REG(SPI0);

}

void spi_wait_for_SPTEF() {
    while( (SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK) == 0) {
        __asm__("nop;");
    }
}

uint8_t spi_is_SPTEF_set() {
    return (SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK);
}

void spi_wait_for_SPRF() {
    while( (SPI_S_REG(SPI0) & SPI_S_SPRF_MASK) == 0) {
        __asm__("nop;");
    }
}

uint8_t spi_is_SPRF_set() {
    return (SPI_S_REG(SPI0) & SPI_S_SPRF_MASK);
}

uint8_t spi_is_SPMF_set() {
    return (SPI_S_REG(SPI0) & SPI_S_SPMF_MASK);
}
