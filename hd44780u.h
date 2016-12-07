/* hd44780u.h - (c) 2016 - burin

    Driver for hd44780u LCD display

    This is a memory mapped hardware driver for
    a 16x4 character LCD display

    for 2^16 address space

    Mapping is as follows:

    RS =  A15 & A12
    R/W = A15 & A13

    E = A15 & ( !/RD # !/WR)

    See defines below:

 */

#ifndef __HD44780U_H__
#define __HD44780U_H__


#define HD44780U_CW     0x8000  // command write       RS=0 /W=0
#define HD44780U_CR     0xA000  // command read (busy) RS=0 /W=1
#define HD44780U_RW     0x9000  // ram write           RS=1 /W=0
#define HD44780U_RR     0xB000  // ram read            RS=1 /W=1

#define HD44780U_CGRAM_SIZE 0x40 
#define HD44780U_DDRAM_SIZE 0x80 

//Registers are "multiplexed" depending on which command is used

#define HD44780U_CMD_CLEAR          0x01
#define HD44780U_CMD_RETURN         0x02
#define HD44780U_CMD_ENTRY          0x04
    #define HD44780U_REG_S              0x01 // 1=display shift, cursor command   
    #define HD44780U_REG_ID             0x02 // 1=increment, 0=decrement     
#define HD44780U_CMD_DISPLAY        0x08
    #define HD44780U_REG_B              0x01 // 1=blink cursor, 0=off
    #define HD44780U_REG_C              0x02 // 1=cursor on, 0=off
    #define HD44780U_REG_D              0x04 // 1=display on, 0=off
#define HD44780U_CMD_CURSOR         0x10
    #define HD44780U_REG_RL             0x04 // 1=shift right,0=shift left
    #define HD44780U_REG_SC             0x08 // 1=display shift, 0=cursor move
#define HD44780U_CMD_FUNCTION       0x20
    #define HD44780U_REG_F              0x04 // 1=5x10 dots, 0=5x8 dots
    #define HD44780U_REG_N              0x08 // 1=2 lines, 0=1 line
    #define HD44780U_REG_DL             0x10 // 1=8 bits, 0=4 bits
#define HD44780U_CMD_CGRAM          0x40
    #define HD44780U_REG_ACG            0x3f // CGRAM address
#define HD44780U_CMD_DDRAM          0x80
    #define HD44780U_REG_ADD            0x7f // DRAM address     

    #define HD44780U_REG_AC             0x7f // address counter     
    #define HD44780U_REG_BF             0x80 // 1=busy, 0=available

// Initialize LCD on power up
void hd44780u_cold_init();

// Initialize LCD on reset (clear memory)
void hd44780u_warm_init();

// Turn display on/off
//  These functions can be used between display updates
void hd44780u_on();
void hd44780u_off();

// Wait for LCD to finish writing
void hd44780u_busy_wait();

// Move current cursor, and set current position
//  (this actually sets the DDRAM address) 
void hd44780u_goto_addr(uint8_t p);

// Set the cursor based on a coordinate system
void hd44780u_goto_xy(uint8_t x, uint8_t y);

// Write characters to current cursor position
void hd44780u_put_ch(uint8_t b); // single character
void hd44780u_put_str(char *s);  // string
uint8_t hd44780u_get_ch();

// Move the cursor forward in the coordinate system
//  wraps around
void hd44780u_cursor_next();

// Clear screen with wipe effect
void hd44780u_wipe(char c);

// Fill screen with character
void hd44780u_fill(char c); 

// Fill *all* DDRAM, including hidden parts
void hd44780u_fill_all(char c);

// Move cursor back to column 0, and increase row
void hd44780u_cursor_return();

// Set CGRAM address for access
void  hd44780u_set_cgram_addr(uint8_t p);

// Save cursor during interrupt
void hd44780u_push_cursor();
void hd44780u_pop_cursor();

#endif
