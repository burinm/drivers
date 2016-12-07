/* x86_64_uart.h - (c) 2016 - burin

    x86_64 platform UART implementation

    Implements uart.h

*/

#ifndef __X86_64_UART_H__
#define __X86_64_UART_H__

#include <stdint.h>

// For bbb platform
uint8_t getchar_blocking();


// Implementation of uart.h

void uart_open();
void uart_close();
void uart_send_byte(uint8_t);
uint8_t uart_get_byte();

// End interface

// Set stdin to ignore escape characters, echo off
void stdin_canonical();
// Undo canonical mode
void stdin_restore();

// Buffer flushing routines
void uart_flush_rx();
void uart_flush_tx();

#endif
