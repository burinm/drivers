#ifndef __6522_H__
#define __6522_H__


void device_6522_init();

// 6522 Registers 16 x 8bit
#define DEVICE_6522_REG_RB          0x0 // Port B, read/write 
#define DEVICE_6522_REG_RA          0x1 // Port A, read/write
#define DEVICE_6522_REG_DDRB        0x2 // Data direction port B
#define DEVICE_6522_REG_DDRA        0x3 // Data direction port A
#define DEVICE_6522_REG_T1CL        0x4 // Timer1 low order latches/counter
#define DEVICE_6522_REG_T1CH        0x5 // Timer1 high order counter
#define DEVICE_6522_REG_T1LL        0x6 // Timer1 low order latches
#define DEVICE_6522_REG_T1LH        0x7 // Timer1 high order latches
#define DEVICE_6522_REG_T2CL        0x8 // Timer2 low order latches/counter
#define DEVICE_6522_REG_T2CH        0x9 // Timer2 high order counter
#define DEVICE_6522_REG_SR          0xa // Shift register
#define DEVICE_6522_REG_ACR         0xb // Auxiliary control register
#define DEVICE_6522_REG_PCR         0xc // Peripheral control register 
    #define DEVICE_6522_CB2_CTRL_MASK        0xe0
        #define DEVICE_6522_CB2_INAE        0x00 // Input negative-active edge
        #define DEVICE_6522_CB2_IIINE       0x20 // Independent interrupt input-negative edge
        #define DEVICE_6522_CB2_IPAE        0x40 // Input-positive active edge 
        #define DEVICE_6522_CB1_IIIPE       0x60 // Independent interrupt input-positive edge
        #define DEVICE_6522_CB1_HO          0x80 // Handshake output 
        #define DEVICE_6522_CB1_PO          0xa0 // Pulse output 
        #define DEVICE_6522_CB1_LO          0xc0 // Low output 
        #define DEVICE_6522_CB1_HI          0xe0 // High output 
    #define DEVICE_6522_CB1_INT_MASK        0x10 // Port B interrupt active edge
    #define DEVICE_6522_CA2_CTRL_MASK        0x0e
        #define DEVICE_6522_CA2_INAE        0x00 // Input negative-active edge
        #define DEVICE_6522_CA2_IIINE       0x02 // Independent interrupt input-negative edge
        #define DEVICE_6522_CA2_IPAE        0x04 // Input-positive active edge 
        #define DEVICE_6522_CA1_IIIPE       0x06 // Independent interrupt input-positive edge
        #define DEVICE_6522_CA1_HO          0x08 // Handshake output 
        #define DEVICE_6522_CA1_PO          0x0a // Pulse output 
        #define DEVICE_6522_CA1_LO          0x0c // Low output 
        #define DEVICE_6522_CA1_HI          0x0e // High output 
    #define DEVICE_6522_CA1_INT_MASK        0x01 // Port A interrupt active edge
            #define DEVICE_6522_INT_NEG_EDGE        0x0
            #define DEVICE_6522_INT_POS_EDGE        0x1
#define DEVICE_6522_REG_IFR         0xd // Interrupt flag register
#define DEVICE_6522_REG_IER         0xe // Interrupt enable register
#define DEVICE_6522_REG_RA2         0xf // Port A, read/write - no handshake

//
#define DEVICE_6522_INPUT           0x0
#define DEVICE_6522_OUTPUT          0x1

#endif
