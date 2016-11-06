#include <stdlib.h>
#include "kl25z.arch/MKL25Z4.h"
#include "frdm_uart.h"
#include "frdm_firmware.h"
#include "../mylib/mylib.h"

circbuf_t *UART0_RX_BUF;
circbuf_t *UART0_TX_BUF;

void setup_uart0() {

    // Port A1,2 is UART0 
    PORTA_PCR1 |= PORT_PCR_MUX(2); //Set Port A, pin 1 to UART0_RX
    PORTA_PCR2 |= PORT_PCR_MUX(2); //Set Port A, pin 2 to UART0_TX

    UART0_C2 &= ~(UART0_C2_TE(1)); //disable transmitter
    UART0_C2 &= ~(UART0_C2_RE(1)); //disable receiver

//Defaults look fine - all 0s
//    UART0_BDH &= ~(UART0_BDH_SBNS(1)); //one stop bit
//    UART0_C1 &= ~(UART0_C1_PE(1)) ; //disable parity
// 8 bit mode  start + 8 data bits(lsb first) + stop
//    UART0_C1 &= ~(UART0_C1_M(1)) ;

// CLOCK_SETUP 1, PEE mode, source external, 96MHz/2 = 48MHZ baud clock
//
// baud =  baud clock
//        -------------
//        (OSR +1) x BR
//
// OSR has to be between 3-31
// BR has to be between 1-8192

#define UART0_BAUD_19200

#ifdef UART0_BAUD_9600
    /* works! */
    // 9600 baud - 48MHz / 9600 (15 +1) = 312.5 = 0x138
    UART0_C4 |= UART0_C4_OSR(15);
    UART0_BDH |= UART0_BDH_SBR(0x1);
    UART0_BDL |= UART0_BDL_SBR(0x38);

    /* does not work */
    // 9600 baud - 48MHz / 9600 (3 +1) = 1250 exactly = 0x4e2 
    //UART0_C4 |= UART0_C4_OSR(3);
    //UART0_BDH |= UART0_BDH_SBR(0x4);
    //UART0_BDL |= UART0_BDL_SBR(0xe2);
#endif

#ifdef UART0_BAUD_19200
    /* works! */
    // 19200 baud - 48MHz / 19200 (15 +1) = 156.25 = 0x9c
    UART0_C4 |= UART0_C4_OSR(15);
    UART0_BDH &= ~(UART0_BDH_SBR_MASK);
    UART0_BDL |= UART0_BDL_SBR(0x9c);

    /* does not work */
    // 19200 baud - 48MHz / 19200 (3 +1) = 625 exactly = 0x271 
    //UART0_C4 |= UART0_C4_OSR(3);
    //UART0_BDH |= UART0_BDH_SBR(0x2);
    //UART0_BDL |= UART0_BDL_SBR(0x71);
#endif

#ifdef UART0_BAUD_115200
    /* outputs garbage  115384 baud...*/
    // 115200 baud - 48MHz / 115200 (15 +1) = 26.04 = 0x1a
    //UART0_C4 |= UART0_C4_OSR(15);
    //UART0_BDH &= ~(UART0_BDH_SBR_MASK);
    //UART0_BDL |= UART0_BDL_SBR(0x1a);

    /* does not work -115384 baud...*/
    // 115200 baud - 48MHz / 115200 (3 +1) = 104.16 = 0x68
    UART0_C4 |= UART0_C4_OSR(3);
    UART0_BDH &= ~(UART0_BDH_SBR_MASK);
    UART0_BDL |= UART0_BDL_SBR(0x68);
#endif

 //39.2.4 UART Control Register 2 (UARTx_C2)
 //UART0_C2 |= UART0_C2_TIE(1); //enable Transmit interrupt
 //UART0_C2 |= UART0_C2_RIE(1); //enable Receive interrupt

    UART0_C2 |= UART0_C2_TE(1); //enable transmitter
    UART0_C2 |= UART0_C2_RE(1); //enable receiver

    // Clear screen
#if 0
    #define CONSOLE_ROWS 24
    for (int i=0;i<CONSOLE_ROWS;i++) { 
        if ( UART0_S1 & UART0_S1_TDRE_MASK) {
            UART0_D = '\n';
            while (!(UART0_S1 & UART0_S1_TC_MASK)) {};
        }
    }
#endif

// Setup global tx/rx buffers
UART0_RX_BUF=circbuf_init(1000);
UART0_TX_BUF=circbuf_init(1000);


// Uart0 interrupts on
__asm__("CPSID i");
NVIC_EnableIRQ(UART0_IRQn);
NVIC_SetPriority(UART0_IRQn, 0);
__asm__("CPSIE i");
}

void start_uart0() {
    UART0_Type *u=UART0;
    //Turn on receive interrupts
    u->C2 |= UART0_C2_RIE(1); //enable transmitter

    u->C2 |= UART0_C2_TE(1); //enable transmitter
    u->C2 |= UART0_C2_RE(1); //enable receiver
}

void stop_uart0() {
    UART0_Type *u=UART0;
    //Turn off receive interrupts
    u->C2 &= ~(UART0_C2_RIE(1)); //disable transmitter
    u->C2 &= ~(UART0_C2_TIE(1)); //disable recieve 

    u->C2 &= ~(UART0_C2_TE(1)); //disable transmitter
    u->C2 &= ~(UART0_C2_RE(1)); //disable receiver
}

void setup_uart1(uint32_t baud) {

UART_Type *u=UART1;

    // Port E0,1 is UART1 
    PORTE_PCR0 |= PORT_PCR_MUX(3); //Set Port E, pin 0 to UART1_TX
    PORTE_PCR1 |= PORT_PCR_MUX(3); //Set Port E, pin 1 to UART1_RX

    // Set UART0 clock source to MCGIRCLK clock
    SIM_SOPT5 &= ~(SIM_SOPT5_UART1RXSRC(0x00)); //UART1_RX pin
    SIM_SOPT5 &= ~(SIM_SOPT5_UART1TXSRC(0x00)); //UART1_TX pin

    u->C2 &= ~(UART_C2_TE(1)); //disable transmitter
    u->C2 &= ~(UART_C2_RE(1)); //disable receiver

    u->BDH &= ~(UART_BDH_SBNS(1)); //one stop bit
    u->C1 &= ~(UART_C1_PE(1)); //disable parity

    // 8 bit mode  start + 8 data bits(lsb first) + stop
    u->C1 &= ~(UART_C1_M(1));
    uint32_t baudbits = SystemCoreClock / (32 * baud);
    u->BDH |= UART_BDH_SBR(baudbits>>8);
    u->BDL |= UART_BDL_SBR(baudbits & 0x000000ff);

    u->C2 |= UART_C2_TE(1); //enable transmitter
    u->C2 |= UART_C2_RE(1); //enable receiver

#if 0
    char message[] = "UART1 hello world";
    for (;;) {
        char* p=message;
        while (*p) {
            if ( u->S1 & UART_S1_TDRE_MASK) {
                UART1_D = (char)*p;
                p++;
                while (!(u->S1 & UART_S1_TC_MASK)) {};
            }
        }
    }
#endif
        while (1) {
            if ( u->S1 & UART_S1_TDRE_MASK) {
                UART1_D = 0x55; 
                while (!(u->S1 & UART_S1_TC_MASK)) {};
            }
        }

}

void write_uart0_va(const char* fmt, ...) {

#include <stdio.h>
    va_list ap;
    //TODO: sketchy fix
    char s[80] = {0};

    va_start(ap, fmt);
    vsnprintf(&s[0],80,fmt,ap);
    va_end(ap);

    write_uart0(&s[0]);
}

void uart0_write_x(uint32_t n) {

    int8_t *result= (int8_t*)calloc(MYLIB_MAX_DIGITS,1);
    my_utoa(result,n,16);

    for (int i=0;i<MYLIB_MAX_DIGITS;i++) {
        if (i > 127 ) { i= 32;}
            uart0_write_byte(*(result + i));
    }
    if (result) { free(result); }
}

void uart0_write_n(uint32_t n) {

    int8_t *result= (int8_t*)calloc(MYLIB_MAX_DIGITS,1);
    my_utoa(result,n,10);

    for (int i=0;i<MYLIB_MAX_DIGITS;i++) {
        if (i > 127 ) { i= 32;}
            uart0_write_byte(*(result + i));
    }
    if (result) { free(result); }
}

void uart0_write_f(float f) {

    uint8_t *result= (uint8_t*)calloc(MAX_FTOA_STRING_LEN,1);
    my_ftoa(f,result);

    for (int i=0;i<MAX_FTOA_STRING_LEN;i++) {
        if (i > 127 ) { i= 32;}
            uart0_write_byte(*(result + i));
    }
    if (result) { free(result); }
}

void _newline();
void _newline() {
    if ( UART0_S1 & UART0_S1_TDRE_MASK) {
        uart0_write_byte('\r');
        uart0_write_byte('\n');
    }
}

void write_uart0(const char* c) {

    while(*c != '\0') {
        if (*c == '\n') {
            _newline();
        } else {
            uart0_write_byte(*c);
        }
        c++;
    }
}

void uart0_write_byte(const char c) {

    LOCK_CBUF
    circbuf_push(UART0_TX_BUF,c);
    UART0->C2 |= UART0_C2_TIE(1);
    UNLOCK_CBUF
}

//Interface implementation

void uart_open() {
    frdm_clocks_init();
    setup_uart0();
    start_uart0();
}

void uart_close() {
    //nop
}

void uart_send_byte(uint8_t b) {
    LOCK_CBUF
    circbuf_push(UART0_TX_BUF,b);
    UART0->C2 |= UART0_C2_TIE(1);
    UNLOCK_CBUF
}

uint8_t uart_get_byte() {
//blocking
uint8_t b=0;

        for(;;) {
            LOCK_CBUF
            if (circbuf_is_poppable(UART0_RX_BUF)) {
                circbuf_pop(UART0_RX_BUF,&b);
                UNLOCK_CBUF
                return b;
            }
            UNLOCK_CBUF
        }
}

//end Interface


