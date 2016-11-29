#include "frdm_spi.h"
#include "frdm_firmware.h"
#include "kl25z.arch/MKL25Z4.h"

#include "util.h" //debugging remove

extern spi_mode_e spi_mode;
extern spi_bitorder_e spi_bitorder;

void try_this_spi_setup() {

    // Turn on port C
    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
    // Turn on SPI0 clock
    SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

    // Set up ports for SPI0
    PORTC->PCR[8] |= PORT_PCR_MUX(1); // ss as gpio pin
    PORTC->PCR[5] |= PORT_PCR_MUX(2);
    PORTC->PCR[6] |= PORT_PCR_MUX(2);
    PORTC->PCR[7] |= PORT_PCR_MUX(2);

    // Set port C, pin 8 data direction to output
    PTC_BASE_PTR->PDDR |= 1<<8;

    SPI_C1_REG(SPI0) = SPI_C1_SPE_MASK;
    SPI_C2_REG(SPI0) = 0x00;

    SPI_C1_REG(SPI0) = SPI_C1_MSTR_MASK | 

                    SPI_C1_SPE_MASK |
                    SPI_C1_CPHA_MASK;
                          
    // prescaler=1, divisor=4 , 24MHz/4 = 6MHz
    SPI_BR_REG(SPI0) = 0x01;
}

void spi_open_device() {

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


spi_set_cpol_cpha(&cpol, &cpha, spi_mode);
SPI_C1_REG(SPI0) = SPI_C1_SPE_MASK |               // SPI system enable
             SPI_C1_MSTR_MASK |                     // SPI master
             ((spi_bitorder == SPI_LSBit) ? SPI_C1_LSBFE_MASK : 0 ) |
             ((cpol == CPOL1) ? SPI_C1_CPOL_MASK : 0) | 
             ((cpha == CPHA1) ? SPI_C1_CPHA_MASK : 0); 
                         
// prescaler=1, divisor=4 , 24MHz/4 = 6MHz
//SPI_BR_REG(SPI0) |= (0x1 & SPI_BR_SPR_MASK);

// prescaler=1, divisor=512 , 24MHz/512 = 46875Hz
//SPI_BR_REG(SPI0) |= (0x8 & SPI_BR_SPR_MASK);

// prescaler=1, divisor=8 , 24MHz/8 = 3MHz
//SPI_BR_REG(SPI0) = (0x2 & SPI_BR_SPR_MASK);

//prescaler=1, divisor=32 , 24MHz/32 = 75KHz
SPI_BR_REG(SPI0) = (0x4 & SPI_BR_SPR_MASK);

spi_ss_high();

}

void spi_close_device() {
    //nop for frdm
}

void spi_ss_low() {
    PTC_BASE_PTR->PCOR |= 1<<8;
}

void spi_ss_high() {
    PTC_BASE_PTR->PSOR |= 1<<8;
}

uint8_t spi_readwrite_byte(volatile uint8_t b) {
uint8_t swap;

spi_wait_for_SPTEF();
SPI_D_REG(SPI0) = b;
spi_wait_for_SPRF();
b = SPI_D_REG(SPI0);

// swap nibbles?
//swap= (b & 0xf0) >> 4;
//b >>= 4;
//b |=swap;
return b;
}

uint8_t spi_read_byte() {
uint8_t b=0;

//untested
spi_wait_for_SPRF();
b=SPI_D_REG(SPI0);
return b;
}

void spi_wait_for_SPTEF() {
    while( (SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK) == 0) {
        __asm__("nop;");
    }
}

uint8_t spi_is_SPTEF_set() {
    return (SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK);
}

/*
uint8_t spi_wait_for_SPRF() {
uint8_t read=0;
    do {
        read = SPI_S_REG(SPI0);
        __asm__("nop;");
    } while( (read & SPI_S_SPRF_MASK) == 0);
return read;
}
*/
void spi_wait_for_SPRF() {
    while( (SPI_S_REG(SPI0) & SPI_S_SPRF_MASK) == 0);
}

uint8_t spi_is_SPRF_set() {
    return (SPI_S_REG(SPI0) & SPI_S_SPRF_MASK);
}

uint8_t spi_is_SPMF_set() {
    return (SPI_S_REG(SPI0) & SPI_S_SPMF_MASK);
}
