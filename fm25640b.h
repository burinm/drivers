#ifndef __FM25640B_H__
#define __FM25640B_H__

/* fm25640b 8K FRAM driver

    extends spi.h
*/

#include <stdint.h>

typedef enum { FM2560B_BLOCK, FM2560B_MEM } fm25640b_fill_e;

#define FM2560B_SIZE (8 * 1024)
#define FM2560B_TEST_FILL   0x99

#define FM2560B_ADDR_MASK_HI    0x1f00  //13 bits
#define FM2560B_ADDR_MASK_LO    0x00ff  


#define FM25640B_CMD_WREN   0x06
#define FM25640B_CMD_WRDI   0x04
#define FM25640B_CMD_READ   0x03
#define FM25640B_CMD_WRITE  0x02

#define FM25640B_CMD_RDSR   0x05
#define FM25640B_CMD_WRSR   0x01
    #define FM25640B_S_WPEN         (1<<7)    
    #define FM25640B_S_UNUSED_MASK  0x70  
    #define FM25640B_S_BP1          (1<<3)    
    #define FM25640B_S_BP0          (1<<2)    
    #define FM25640B_S_WEL          (1<<1)    
    #define FM25640B_S_DONT_CARE    (1<<0)    

#define FM25640B_CMD_NOP    0xff


void fm25640b_open(void);
void fm25640b_close(void);

// Fill with single character pattern
void fm25640b_write_block(uint16_t addr, uint8_t b, uint16_t size);
// Copy memory contents
void fm25640b_write_mem(uint16_t addr, uint8_t *b, uint16_t size);

void fm25640b_write_byte(uint16_t addr, uint8_t b);
uint8_t fm25640b_read_byte(uint16_t addr);

uint8_t fm25640b_get_status(void);

//Set in non-volatile memory
void fm25640b_set_write_enable(void);
void fm25640b_set_write_disable(void);

//private
void __fm25640b_write_block(uint16_t addr, uint8_t *b, uint16_t size, fm25640b_fill_e fill);

#endif
