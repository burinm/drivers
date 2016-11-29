#ifndef __KL25Z_UART_H__
#define __KL25Z_UART_H__


/* Platform driver for NXP Freedom KL25Z development board
    
    UART
*/


#include <stdint.h>
#include <stdarg.h>
#include "mylib.h"

//Interface implementation

void uart_open();
void uart_close();
void uart_send_byte(uint8_t);
uint8_t uart_get_byte();

void uart_flush_rx();
void uart_flush_tx();

//end Interface


void setup_uart0();
void setup_uart1(uint32_t baud);
void start_uart0();
void stop_uart0();

void write_uart0(const char* c);
void write_uart0_va(const char* c, ...);
void uart0_write_x(uint32_t n);
void uart0_write_n(uint32_t n);
void uart0_write_f(float f);
void uart0_write_byte(const char c);

#ifdef CIRCBUF_TINY
extern circbuf_tiny_t *UART0_RX_BUF;
extern circbuf_tiny_t *UART0_TX_BUF;
#else
extern circbuf_t *UART0_RX_BUF;
extern circbuf_t *UART0_TX_BUF;
#endif

#define LOCK_CBUF   __asm__("CPSID i");
#define UNLOCK_CBUF __asm__("CPSIE i");

#endif
