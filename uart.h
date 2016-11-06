#ifndef __UART_H__
#define __UART_H__

//Interface, these must be implemented by platform

extern void uart_open();
extern void uart_close();
extern void uart_send_byte(uint8_t);
extern uint8_t uart_get_byte();



#endif
