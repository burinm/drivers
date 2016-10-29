#ifndef __KL25Z_UART_H__
#define __KL25Z_UART_H__

#include <stdint.h>
#include <stdarg.h>
#include "mylib.h"

void write_uart0(const char* c);
void write_uart0_va(const char* c, ...);
void uart0_write_x(uint32_t n);
void uart0_write_n(uint32_t n);
void uart0_write_f(float f);
void uart0_write_byte(const char c);

extern circbuf_t *UART0_RX_BUF;
extern circbuf_t *UART0_TX_BUF;

#define LOCK_CBUF   __asm__("CPSID i");
#define UNLOCK_CBUF __asm__("CPSIE i");

#endif
