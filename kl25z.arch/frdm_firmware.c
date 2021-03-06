/* frdm_firmware.c - (c) 2016 - burin */

#include "frdm_firmware.h"
#include <stdlib.h> //malloc
#include <stdio.h> //snprintf
#include "frdm_uart.h"
#include "mylib.h"

uint8_t uart0_receive_mode=0;

static int8_t current_color=0;
static uint32_t zero __attribute__((aligned(4))) =0;
static uint32_t pit_period=0xfffffffe;

//DMA chaining
uint8_t dma_chain=0;
uint32_t *dma_chain_source=0;
uint32_t *dma_chain_dest=0;
uint32_t dma_chain_size=0; 

color_addr_t COLORS_ADDR[3] = {
{ RED, TPM2, 0, 50, 50},
{ GREEN, TPM2, 1, 50, 50},
{ BLUE, TPM0, 1, 50, 50}
};

void frdm_clocks_init() {
//TODO: Let each module call this with
// an argument and the Gates it needs turned on

SystemCoreClockUpdate();

//This actually allocates pointers to these resources...

    //12.2.9 System Clock Gating Control Register 5 (SIM_SCGC5)
    // Attach port B
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
    // Attach port D
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

    // Attach port E - Uart1 test
    SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

    // Attach port A - Uart0
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

    //12.2.8 System Clock Gating Control Register 4 (SIM_SCGC4)
    // Turn on SIM clock for gate for UART0
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

    //Uart 1 test
    SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;

    //Turn on TPM2
    SIM_SCGC6 |= SIM_SCGC6_TPM2(1);
    //Turn on TPM0
    SIM_SCGC6 |= SIM_SCGC6_TPM0(1);

    // Set UART0 clock source to MCGIRCLK clock
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(0x01);
    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL(0x01); //PLL clock select /2

    //Source clock for TPM counter
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0x01); // MCGFLLCLK clock or MCGPLLCLK/2
    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL(0x01); //PLL/FLL clock select
}

void setup_tpm_center(TPM_Type* tpm) {


//TODO: Check that all TPM channels are in CPWM mode,
//      they all have to be in CPWM mode

    /* Using Center PWM mode to achieve duty cycle

        CCR, MOD, CnV
        ftimer = fcounter / Prescaler *(CC +1)

        Center aligned PWM
        Waveform period = 2 x MOD
        Pulse width = 2 x Cnv
    */

    tpm->SC = 0; //known state
    tpm->SC &= ~(TPM_SC_TOIE_MASK); // Disable Timer Overflow Interrupt

    tpm->SC |= TPM_SC_CMOD(0x01);   //LPTPM increments on every LPTPM counter clock

    // LPTPM in up/down counting mode
    //  This is also required for Center-aligned PWM 
    tpm->SC |= TPM_SC_CPWMS_MASK; // LPTPM in up/down counting mode

    tpm->SC &= ~(TPM_SC_PS(0x7));   //Prescaler = 0 = divide by 1

    // Count until MOD mode
    tpm->SC &= ~(TPM_CNT_COUNT(0x0)); // LPTPM counter value = 0

    // Range 0x0000 -> 0x7FFF in Center aligned mode
    // TODO: figure out what frequency this is
    tpm->MOD |= TPM_MOD_MOD(0x3ff); 

}

void tpm_setup_duty(color_addr_t *c) {
/* These bits have to be set together

    Clear Output on match-up, Set Output on match-down
    Force output to match when counting changes direction

*/
(c->TPM)->CONTROLS[c->channel].CnSC |=
    (TPM_CnSC_MSB(0x1) |TPM_CnSC_ELSB(0x1) );

(c->TPM)->CONTROLS[c->channel].CnV |=
     (TPM_CnV_VAL((c->TPM)->MOD) * (100-(c->duty))/100);

(c->TPM)->SC |=TPM_SC_TOIE(1); //Enable Timer Overflow Interrupt

if (c->c == RED) {
    red_tpm_mode();
}

if (c->c == GREEN) {
   green_tpm_mode(); 
}

if (c->c == BLUE) {
   blue_tpm_mode(); 
}

}

void tpm_set_duty(color_addr_t* c) {
    (c->TPM)->CONTROLS[c->channel].CnV =
         TPM_CnV_VAL((c->TPM)->MOD) * (100-(c->duty))/100;
}

// LEDs on
void red_gpio_mode() {
    PORTB_PCR18 = PORT_PCR_MUX(1); //Set port B, pin 18 to GPIO pin
    PTB_BASE_PTR->PDDR |= 1<<18; //Set port B, pin 18 data direction to output
}

void green_gpio_mode() {
    PORTB_PCR19 = PORT_PCR_MUX(1); //Set port B, pin 19 to GPIO pin
    PTB_BASE_PTR->PDDR |= 1<<19; //Set port B, pin 19 data direction to output
}

void blue_gpio_mode() {
    PORTD_PCR1 = PORT_PCR_MUX(1); //Set port D, pin 18 to GPIO pin
    PTD_BASE_PTR->PDDR |= 1<<1; //Set port D, pin 18 data direction to output
}

void red_tpm_mode() {
    PORTB_PCR18 |= PORT_PCR_MUX(3);
}

void green_tpm_mode() {
    PORTB_PCR19 |= PORT_PCR_MUX(3);
}

void blue_tpm_mode() {
    PORTD_PCR1 |= PORT_PCR_MUX(4);
}

inline void blue_led_on() {
    PTD_BASE_PTR->PCOR |= 1<<1;
}

inline void blue_led_off() {
    PTD_BASE_PTR->PSOR |= 1<<1;
}

inline void green_led_on() {
    PTB_BASE_PTR->PCOR |= 1<<19;
}

inline void green_led_off() {
    PTB_BASE_PTR->PSOR |= 1<<19;
}

inline void blue_led_toggle() {
    PTD_BASE_PTR->PTOR |= 1<<1;
}

// Pit timer 0, used for profiling. Always set at max
void setup_pit_timer() {
/* ALL the documentaion conflicts with the API
     for the PIT module..
*/

//Enables pit memory access as well
SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

// 32.3.1 PIT Module Control Register (PIT_MCR)
//  Set this to enabled before any other setup
PIT->MCR &= ~(PIT_MCR_MDIS_MASK);

// Timer0 - Load start value -down counter
//   Don't leave this 0. The timer will cause starvation...
PIT->CHANNEL[0].LDVAL = 0xfffffffe & PIT_LDVAL_TSV_MASK;
// Timer0 - Clear Timer Interrupt flag by writing 1
PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; 


// Pit timer interrupts on
__asm__("CPSID i");
NVIC_EnableIRQ(PIT_IRQn);
NVIC_SetPriority(PIT_IRQn, 0);
__asm__("CPSIE i");
}

inline void start_pit_timer() {
// Reset load value
PIT->CHANNEL[0].LDVAL = 0xfffffffe & PIT_LDVAL_TSV_MASK;
// Timer0 - Turn on interrupts and enable
PIT->CHANNEL[0].TCTRL |= (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
} 

inline void stop_pit_timer() {
// Timer0 - Turn off interrupts and disable
PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
// Timer0 - Clear Timer Interrupt flag by writing 1
PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; 

} 

// Pit timer 1
void setup_pit_timer1(uint32_t p) {
pit_period = p;

//Enables pit memory access as well
SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

// 32.3.1 PIT Module Control Register (PIT_MCR)
//  Set this to enabled before any other setup
PIT->MCR &= ~(PIT_MCR_MDIS_MASK);

// Timer0 - Load start value -down counter
//   Don't leave this 0. The timer will cause starvation...
PIT->CHANNEL[1].LDVAL = pit_period & PIT_LDVAL_TSV_MASK;
// Timer0 - Clear Timer Interrupt flag by writing 1
PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK; 


// Pit timer interrupts on
__asm__("CPSID i");
NVIC_EnableIRQ(PIT_IRQn);
NVIC_SetPriority(PIT_IRQn, 0);
__asm__("CPSIE i");
}

inline void start_pit_timer1() {
// Reset load value
PIT->CHANNEL[1].LDVAL = pit_period & PIT_LDVAL_TSV_MASK;
// Timer0 - Turn on interrupts and enable
PIT->CHANNEL[1].TCTRL |= (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
} 

inline void stop_pit_timer1() {
// Timer0 - Turn off interrupts and disable
PIT->CHANNEL[1].TCTRL &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
// Timer0 - Clear Timer Interrupt flag by writing 1
PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK; 

} 

uint8_t is_pit_timer_running() {
 return (PIT->CHANNEL[0].TCTRL & PIT_TCTRL_TEN_MASK);
} 

inline uint32_t pit_read_timer0() {
    return PIT->CHANNEL[0].CVAL;
}

void pit_read_64bit_timer(uint32_t *high, uint32_t *low) {
// 32.3.2 PIT Upper/Lower Lifetime Timer Register
//  Read in this order
*high = (PIT->LTMR64H) & PIT_LTMR64H_LTH_MASK;
*low = (PIT->LTMR64L) & PIT_LTMR64L_LTL_MASK;
} 

//TODO: Move the following into a utility file, not really firmware
//private functions
uint8_t set_leds(uint8_t s) {

    switch(s) { //This isn't frequently hit code...

        case 'p':
            led_brightness_decrease(&COLORS_ADDR[RED]);
            led_brightness_decrease(&COLORS_ADDR[GREEN]);
            led_brightness_decrease(&COLORS_ADDR[BLUE]);
            break;

        case 'P':
            led_brightness_increase(&COLORS_ADDR[RED]);
            led_brightness_increase(&COLORS_ADDR[GREEN]);
            led_brightness_increase(&COLORS_ADDR[BLUE]);
            break;

        case 'o':
            led_brightness_increase(&COLORS_ADDR[RED]);
            break;

        case 'i':
            led_brightness_decrease(&COLORS_ADDR[RED]);
            break;

        case 'u':
            led_brightness_increase(&COLORS_ADDR[GREEN]);
            break;

        case 'y':
            led_brightness_decrease(&COLORS_ADDR[GREEN]);
            break;

        case 'j':
            led_brightness_increase(&COLORS_ADDR[BLUE]);
            break;

        case 'h':
            led_brightness_decrease(&COLORS_ADDR[BLUE]);
            break;

/*
        case 't':
            uart0_write(pit_read_timer0());
            break;
*/

        case 'n':
            led_set_color(current_color);
            break;
    
        case 'q':
            uart0_receive_mode=1;
            break;

        case 'w':
            uart0_receive_mode=0;
            break;

        default:
            return 0;
            break;
    }
return 1;
}

void led_brightness_increase(color_addr_t* c) {

    c->brightness++;
    if (c->brightness > 100) { c->brightness = 100; }

    c->duty=c->brightness;
    
    tpm_set_duty(c);
}

void led_brightness_decrease(color_addr_t* c) {

    c->brightness--;
    if (c->brightness <0) { c->brightness = 0; }
    c->duty=c->brightness;

    tpm_set_duty(c);
}

void led_set_color() {

    COLORS_ADDR[RED].duty=0;
    COLORS_ADDR[GREEN].duty=0;
    COLORS_ADDR[BLUE].duty=0;

    if (current_color & RED_BITS) {
        COLORS_ADDR[RED].duty =
            COLORS_ADDR[RED].brightness;
    }

    if (current_color & GREEN_BITS) {
        COLORS_ADDR[GREEN].duty =
            COLORS_ADDR[GREEN].brightness;
    }

    if (current_color & BLUE_BITS) {
        COLORS_ADDR[BLUE].duty =
            COLORS_ADDR[BLUE].brightness;
    }

    tpm_set_duty(&COLORS_ADDR[RED]);
    tpm_set_duty(&COLORS_ADDR[GREEN]);
    tpm_set_duty(&COLORS_ADDR[BLUE]);

    current_color++;
    if (current_color == NUM_RGB) { current_color=0; }
}

//DMA routines

void setup_dma0() {
// DMA channel 1 interrupts on         
__asm__("CPSID i");
NVIC_EnableIRQ(DMA0_IRQn);    
NVIC_SetPriority(DMA0_IRQn, 0);
__asm__("CPSIE i");            
} 

void disable_dma0() {
// DMA channel 1 interrupts on         
__asm__("CPSID i");
NVIC_DisableIRQ(DMA0_IRQn);    
__asm__("CPSIE i");            
} 

inline uint8_t dma0_memmove_8(uint8_t channel, uint32_t *source, uint32_t *dest, uint32_t size) {
return _dma0_memmove(channel, source, dest, size, 1, 0);
}

inline uint8_t dma0_memmove(uint8_t channel, uint32_t *source, uint32_t *dest, uint32_t size) {
return _dma0_memmove(channel, source, dest, size, 0, 0);
}

inline uint8_t dma0_memzero(uint8_t channel, uint32_t *dest, uint32_t size) {
return _dma0_memmove(channel, dest, dest, size, 0, 1);
}

inline uint8_t dma0_memzero_8(uint8_t channel, uint32_t *dest, uint32_t size) {
return _dma0_memmove(channel, dest, dest, size, 1, 1);
}

uint8_t _dma0_memmove(uint8_t channel, uint32_t *source, uint32_t *dest, uint32_t size, uint8_t tsize, uint8_t memzero) {

    if (channel > 3 ) { return DMA_CHANNEL_ERROR; }
    if (size > 0x000FFFFF ) { return DMA_SIZE_ERROR; }

    if (! _is_valid_dma_address(source) ) {return DMA_SRC_ADDRESS_INVALID; }
    if (! _is_valid_dma_address(dest) ) {return DMA_DST_ADDRESS_INVALID; }

if (! memzero ) {
    // Logic for overlapping pieces, reverse transfer order if
    // destination is lower in memory than source

    if (source == dest) { return 0; } // case 1)
    
    uint32_t slength = size - 1; // 0 based length
    if ( ((uint32_t *)(source + slength) < dest) //case 2)
         || ((uint32_t *)(dest + slength) < source) // case 2)
         || (((uint32_t *)(dest + slength) > source) && (dest < source)) ) // case 4)
    {
        //Do nothing
    } else { // Must be case 3)
        // Since DMA doesn't can't count backwards in this system,
        //  we must set up two transfers

        // Setup a second DMA to execute after the first
        dma_chain=1;
        dma_chain_source=source;
        dma_chain_dest=dest;
        dma_chain_size= (uint32_t)dest-(uint32_t)source;

        // Part 1, copy overlap at end of source first
        //  This starts at dest's address and ends at the
        //  end of source
        uint32_t *tmp_dest = dest;
        dest = (uint32_t *)((uint32_t)source + slength);
        source = tmp_dest;
        size = size - ((uint32_t)dest-(uint32_t)source);

    }
} else {
    source=&zero;
}

    // Setup Transfer Control Descriptor

    DMA_SAR(channel)=(uint32_t)source;
    DMA_DAR(channel)=(uint32_t)dest;

    //Sanity check
    if (!  (DMA_SAR(channel) == (uint32_t)source) ) {
        return DMA_ADDRESS_CHECK_FAILED;
    }
    if (!  (DMA_DAR(channel) == (uint32_t)dest) ) {
        return DMA_ADDRESS_CHECK_FAILED;
    }

    // Set Transfer Size
    DMA_DSR_BCR(channel) = DMA_DSR_BCR_BCR(size);

    //Start Transfer
    DMA_DCR(channel) = DMA_DCR_START_MASK //start transfer
                        | DMA_DCR_DSIZE(tsize)
                        | DMA_DCR_SSIZE(tsize)
                        | ( memzero ? 0 : DMA_DCR_SINC_MASK) //increase source count
                        | DMA_DCR_DINC_MASK //increase dest count
                        | DMA_DCR_EINT_MASK; //interrupt on completion

    // Check configuration
    // 32-bit transfers sizes must be 4 bytes, 16-bits 2 byte
    if (DMA_DSR_BCR(channel) & DMA_DSR_BCR_CE_MASK) { return DMA_CONFIGURATION_ERROR;}
    
    
    //DMA_DSR(channel) [DONE]=set - stops channel...
return OK;
}

inline uint8_t _is_valid_dma_address(uint32_t *addy) {
 return ( ((uint32_t)addy & DMA_ADDY_MASK) == DMA_ADDY_RANGE_0 ||
          ((uint32_t)addy & DMA_ADDY_MASK) == DMA_ADDY_RANGE_1 ||
          ((uint32_t)addy & DMA_ADDY_MASK) == DMA_ADDY_RANGE_2 ||
          ((uint32_t)addy & DMA_ADDY_MASK) == DMA_ADDY_RANGE_3 ); 
}

inline uint8_t is_dma_done(uint8_t channel) {
        return ( DMA_DSR_BCR(channel) & DMA_DSR_BCR_DONE_MASK );
}
