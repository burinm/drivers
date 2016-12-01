#ifndef __UART_H__
#define __UART_H__

/* Protocol driver for UART

    Implements protocol for generic UART driver

*/

// UART Interfacei Definition:
//  These must be implemented by platform

// Device specific open/close
extern void uart_open();
extern void uart_close();

// Device specific send byte
extern void uart_send_byte(uint8_t);
extern uint8_t uart_get_byte();

// Flush queues and buffers
extern void uart_flush_rx();
extern void uart_flush_tx();

// End interface

#endif
