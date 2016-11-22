include "fm25640b.h"
#include "spi.h"


void fm25640b_open() {
//This device can use 0, or 3
    spi_set_mode(SPI_MODE_0);
    spi_set_bitorder(SPI_MSBit);
    spi_open_device();
}

void fm25640b_close() {
    //Disable writes on device
    spi_start_transaction();    
    (void)spi_readwrite_byte(FM25640B_CMD_WRDI);
    spi_stop_transaction();
}

uint8_t fm25640b_get_status() {
uint8_t out=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_RDSR);
    out = spi_readwrite_byte(FM25640B_CMD_NOP);
    spi_stop_transaction();
}

void fm25640b_write_status(uint8_t) {


}

void fm25640b_write_block(uint16_t addr, uint16_t size, uint8_t *b) {
    spi_start_transaction();
//Check that we need both WREN, WRITE...
    (void)spi_readwrite_byte(FM25640B_CMD_WREN);
    (void)spi_readwrite_byte(FM25640B_CMD_WRITE);
    (void)spi_readwrite_byte((addr >> 8) & FM2560B_ADDR_MASK_HI);
    (void)spi_readwrite_byte(addr & FM2560B_ADDR_MASK_LO);
    for (i=0;i<size;i++) {
         (void)spi_readwrite_byte(*(uint8_t*)(b + i));
    }
    spi_stop_transaction();
}

uint8_t fm25640b_read_byte(uint16_t addr) {
    uint8_t out=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(FM25640B_CMD_READ);
    (void)spi_readwrite_byte((addr >> 8) & FM2560B_ADDR_MASK_HI);
    (void)spi_readwrite_byte(FM25640B_CMD_RDSR);
    out = spi_readwrite_byte(FM25640B_CMD_NOP);
    spi_stop_transaction();
}
