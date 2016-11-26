#include "fm25640b.h"
#include "spi.h"


void fm25640b_open(void) {
//TODO - implement this, right now works out as Mode 0
//This device can use 0, or 3
// Mode 0  - CLK is low, then bring /SS low

    spi_set_mode(SPI_MODE_0);
    spi_set_bitorder(SPI_MSBit);
    spi_open_device();
}

void fm25640b_close(void) {
    //Disable writes on device
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_WRDI);
    spi_stop_transaction();
}

uint8_t fm25640b_get_status(void) {
uint8_t out=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_RDSR);
    out = spi_readwrite_byte(FM25640B_CMD_NOP);
    spi_stop_transaction();
return out;
}

void fm25640b_set_write_enable(void) {
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_WREN);
    spi_stop_transaction();
}

void fm25640b_set_write_disable(void) {
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_WRDI);
    spi_stop_transaction();
}


void fm25640b_write_block(uint16_t addr, uint8_t b, uint16_t size) {
    __fm25640b_write_block(addr,&b,size,FM2560B_BLOCK);
}
void fm25640b_write_mem(uint16_t addr, uint8_t *b, uint16_t size) {
    __fm25640b_write_block(addr,b,size,FM2560B_MEM);
}

void __fm25640b_write_block(uint16_t addr, uint8_t *b, uint16_t size, fm25640b_fill_e fill) {
uint16_t i;
    fm25640b_set_write_enable();
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_WRITE);
    (void)spi_readwrite_byte((addr & FM2560B_ADDR_MASK_HI) >> 8 );
    (void)spi_readwrite_byte(addr & FM2560B_ADDR_MASK_LO);
    for (i=0;i<size;i++) {
            (fill == FM2560B_MEM ) ?
                (void)spi_readwrite_byte(*(uint8_t*)(b + i)) :
                (void)spi_readwrite_byte(*b);
    }
    spi_stop_transaction();
    fm25640b_set_write_disable();
}

void fm25640b_write_byte(uint16_t addr, uint8_t b) {
    fm25640b_set_write_enable();
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_WRITE);
    (void)spi_readwrite_byte((addr & FM2560B_ADDR_MASK_HI) >> 8 );
    (void)spi_readwrite_byte(addr & FM2560B_ADDR_MASK_LO);
    (void)spi_readwrite_byte(b);
    spi_stop_transaction();
    fm25640b_set_write_disable();
}

uint8_t fm25640b_read_byte(uint16_t addr) {
    uint8_t out=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_READ);
    (void)spi_readwrite_byte((addr & FM2560B_ADDR_MASK_HI) >> 8 );
    (void)spi_readwrite_byte(addr & FM2560B_ADDR_MASK_LO);
    out = spi_readwrite_byte(FM25640B_CMD_NOP);
    spi_stop_transaction();
return out;
}
