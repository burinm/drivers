/* 6522.h - (c) 2016 - burin

    65c22 VIA I/O expander driver

    This is a memory mapped driver for any
    2^16 address space device
*/ 

#ifndef __6522_H__
#define __6522_H__

#include <stdint.h>

// 6522 Registers 16 x 8bit
#define DEVICE_6522_NUM_REG         16

// Port A, read/write - no handshake
#define DEVICE_6522_REG_RA2         0xf

// Interrupt enable register
#define DEVICE_6522_REG_IER         0xe
    #define DEVICE_6522_SET_IER             0x80
        #define DEVICE_6522_INT_DIS                 0x0
        #define DEVICE_6522_INT_ENB                 0x1
    #define DEVICE_6522_T1_IER              0x40
    #define DEVICE_6522_T2_IER              0x20
    #define DEVICE_6522_CB1_IER             0x10
    #define DEVICE_6522_CB2_IER             0x08
    #define DEVICE_6522_SHIFT_IER           0x04
    #define DEVICE_6522_CA1_IER             0x02
    #define DEVICE_6522_CA2_IER             0x01

// Interrupt flag register
#define DEVICE_6522_REG_IFR         0xd
    #define DEVICE_6522_ALL_IFR             0x80
    #define DEVICE_6522_T1_IFR              0x40
    #define DEVICE_6522_T2_IFR              0x20
    #define DEVICE_6522_CB1_IFR             0x10
    #define DEVICE_6522_CB2_IFR             0x08
    #define DEVICE_6522_SHIFT_IFR           0x04
    #define DEVICE_6522_CA1_IFR             0x02
    #define DEVICE_6522_CA2_IFR             0x01

// Peripheral control register 
#define DEVICE_6522_REG_PCR         0xc
    #define DEVICE_6522_CB2_CTRL_MASK       0xe0 // CB2 Control
        #define DEVICE_6522_CB1_HI                  0xe0 // High output 
        #define DEVICE_6522_CB1_LO                  0xc0 // Low output 
        #define DEVICE_6522_CB1_PO                  0xa0 // Pulse output 
        #define DEVICE_6522_CB1_HO                  0x80 // Handshake output 
        #define DEVICE_6522_CB1_IIIPE               0x60 // Independent interrupt input-positive edge
        #define DEVICE_6522_CB2_IPAE                0x40 // Input-positive active edge 
        #define DEVICE_6522_CB2_IIINE               0x20 // Independent interrupt input-negative edge
        #define DEVICE_6522_CB2_INAE                0x00 // Input negative-active edge
    #define DEVICE_6522_CB1_INT_MASK        0x10 // CB1 interrupt active edge

    #define DEVICE_6522_CA2_CTRL_MASK       0x0e // CA2 Control
        #define DEVICE_6522_CA1_HI                  0x0e // High output 
        #define DEVICE_6522_CA1_LO                  0x0c // Low output 
        #define DEVICE_6522_CA1_PO                  0x0a // Pulse output 
        #define DEVICE_6522_CA1_HO                  0x08 // Handshake output 
        #define DEVICE_6522_CA1_IIIPE               0x06 // Independent interrupt input-positive edge
        #define DEVICE_6522_CA2_IPAE                0x04 // Input-positive active edge 
        #define DEVICE_6522_CA2_IIINE               0x02 // Independent interrupt input-negative edge
        #define DEVICE_6522_CA2_INAE                0x00 // Input negative-active edge
    #define DEVICE_6522_CA1_INT_MASK        0x01 // CA1 interrupt active edge

            #define DEVICE_6522_INT_POS_EDGE        0x1
            #define DEVICE_6522_INT_NEG_EDGE        0x0

// Auxiliary control register
#define DEVICE_6522_REG_ACR         0xb
    #define DEVICE_6522_T1_CTRL_MASK        0xc0
        #define DEVICE_6522_T1_CONT_SW_IRQ          0xc0 // Continuous interrupts, PB7 square wave
        #define DEVICE_6522_T1_LOAD_OS_IRQ          0x80 // Interrupt on timer load, PB7 one shot
        #define DEVICE_6522_T1_CONT_IRQ             0x40 // Continuous interrupts
        #define DEVICE_6522_T1_LOAD_IRQ             0x00 // Interrupt on timer load, PB7 disabled
    #define DEVICE_6522_T2_CTRL_MASK        0x20 // 0 - Timed interrupt, 1 - Count down PB6
    #define DEVICE_6522_SHIFT_MODE_MASK     0x1c
    #define DEVICE_6522_PB_LATCH_MASK       0x02
    #define DEVICE_6522_PA_LATCH_MASK       0x01

             #define DEVICE_6522_LATCH_ENB          0x1
             #define DEVICE_6522_LATCH_DIS          0x0

// Shift register
#define DEVICE_6522_REG_SR          0xa
    #define DEVICE_6522_SR_MODE_MASK        0x1c

            // Register 0xb and 0xa shift register modes
            #define DEVICE_6522_SR_MODE7         0x1c // Shift out, external clock CB1
            #define DEVICE_6522_SR_MODE6         0x18 // Shift out, O2 control
            #define DEVICE_6522_SR_MODE5         0x14 // Shift out, T2 control
            #define DEVICE_6522_SR_MODE4         0x10 // Shift out, T2 free running
            #define DEVICE_6522_SR_MODE3         0x0c // Shift in, external clock CB1
            #define DEVICE_6522_SR_MODE2         0x08 // Shift in, O2 control
            #define DEVICE_6522_SR_MODE1         0x04 // Shift in, T2 control
            #define DEVICE_6522_SR_MODE0         0x00 // Disabled

// Timer2 high order counter
#define DEVICE_6522_REG_T2CH        0x9

// Timer2 low order latches/counter
#define DEVICE_6522_REG_T2CL        0x8

// Timer1 high order latches
#define DEVICE_6522_REG_T1LH        0x7

// Timer1 low order latches
#define DEVICE_6522_REG_T1LL        0x6

// Timer1 high order counter
#define DEVICE_6522_REG_T1CH        0x5

// Timer1 low order latches/counter
#define DEVICE_6522_REG_T1CL        0x4

// Data direction port A
#define DEVICE_6522_REG_DDRA        0x3
    #define DEVICE_6522_DD_INPUT           0x0
    #define DEVICE_6522_DD_OUTPUT          0x1

// Data direction port B
#define DEVICE_6522_REG_DDRB        0x2

// Port A, read/write
#define DEVICE_6522_REG_RA          0x1

// Port B, read/write 
#define DEVICE_6522_REG_RB          0x0

// Interface start
extern void device_6522_init(uint8_t* addr);
// Interface end 


//Unfortunately not all compilers support inline, so 
// sacrificing type safety for speed/compact code

//  All functions below take starting address of peripheral (a) uint16_t

//Today, I became a C programmer...

// Set data direction to out for Port A, pin n
#define DEVICE_6522_SET_DDA_OUT(a, bit_n) \
    (*(a + DEVICE_6522_REG_DDRA) = *(a + DEVICE_6522_REG_DDRA) | (1<<bit_n))

// Set data direction to in for Port A, pin n
#define DEVICE_6522_SET_DDA_IN(a, bit_n) \
    (*(a + DEVICE_6522_REG_DDRA) = *(a + DEVICE_6522_REG_DDRA) & ~(1<<bit_n)); 

// Set data direction to out for Port B, pin n
#define DEVICE_6522_SET_DDB_OUT(a, bit_n) \
    (*(a + DEVICE_6522_REG_DDRB) = *(a + DEVICE_6522_REG_DDRB) | (1<<bit_n))

// Set data direction to in for Port B, pin n
#define DEVICE_6522_SET_DDB_IN(a, bit_n) \
    (*(a + DEVICE_6522_REG_DDRB) = *(a + DEVICE_6522_REG_DDRB) & ~(1<<bit_n))

// Read port A, returns uint8_t
#define DEVICE_6522_READ_A(a) \
    (*(a + DEVICE_6522_REG_RA))

// Read port B, returns uint8_t
#define DEVICE_6522_READ_B(a) \
    (*(a + DEVICE_6522_REG_RB))

// Write port A, takes uint8_t
#define DEVICE_6522_WRITE_A(a, b) \
    (*(a + DEVICE_6522_REG_RA) = b)

// Write port B, takes uint8_t
#define DEVICE_6522_WRITE_B(a, b) \
    (*(a + DEVICE_6522_REG_RB) = b)

#endif
