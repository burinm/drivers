#ifndef __X86_64_UART_H__
#define __X86_64_UART_H__

#include <stdint.h>

//Interface, these must be implemented by platform

extern void uart_open();
extern void uart_close();
extern void uart_send_byte(uint8_t);
extern uint8_t uart_get_byte();



#endif
