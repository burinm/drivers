#ifndef __X86_64_UART_H__
#define __X86_64_UART_H__

/* x86_64 platform UART implementation

    Implements uart.h

*/

#include <stdint.h>

//Interface, these must be implemented by platform

extern void uart_open();
extern void uart_close();
extern void uart_send_byte(uint8_t);
extern uint8_t uart_get_byte();

void uart_flush_rx();
void uart_flush_tx();

//end interface

void stdin_canonical();
void stdin_restore();
void uart_flush_rx();
void uart_flush_tx();

#endif
