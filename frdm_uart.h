/* frdm_uart.h - (c) 2016 - burin

    Platform driver for NXP Freedom KL25Z development board
    
    UART0, UART1 setup, control fucntions
*/

#ifndef __KL25Z_UART_H__
#define __KL25Z_UART_H__

#include <stdint.h>
#include <stdarg.h>
#include "mylib.h"

// Implements interface uart.h

void uart_open();
void uart_close();
void uart_send_byte(uint8_t);
uint8_t uart_get_byte();

void uart_flush_rx();
void uart_flush_tx();

//end Interface


// Turn on clock, device and set baud rate
void setup_uart0();
// Turn on clock, device and set baud rate
//  Baud rate parameter currently unused
void setup_uart1(uint32_t baud);

// Actually enable/disable transmitter
void start_uart0();
void stop_uart0();

// Functions for logging/printing to UART
void write_uart0(const char* c);            // char string
void write_uart0_va(const char* c, ...);    // printf like
void uart0_write_x(uint32_t n);             // integer, hex format
void uart0_write_n(uint32_t n);             // integer, integer format
void uart0_write_f(float f);                // float, integer format
void uart0_write_byte(const char c);        // write single char

// Compile time option for tiny (255 byte/fast) circular buffer
#ifdef CIRCBUF_TINY
extern circbuf_tiny_t *UART0_RX_BUF;
extern circbuf_tiny_t *UART0_TX_BUF;
#else
extern circbuf_t *UART0_RX_BUF;
extern circbuf_t *UART0_TX_BUF;
#endif

// For circular buffer critical sections
#define LOCK_CBUF   __asm__("CPSID i");
#define UNLOCK_CBUF __asm__("CPSIE i");

#endif
