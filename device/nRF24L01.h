/* nRF24L01.h - (c) 2016 - burin

    nrf24L01 Nordic wireless tranceiver driver

    Extends spi.h
*/

#ifndef __NRF24L01_H__
#define __NRF24L01_H__


#include <stdint.h>

typedef struct {
            uint8_t high;
            uint32_t low;
} __attribute__ ((__packed__))  nrf_5byte_t;

#define SPI_CPOL            IDLE_LOW 
#define SPI_CPHA            SECOND_EDGE 

//Commands

#define NRF_COMMAND_WORD_ORDER      MSB 
#define NRF_DATA_BYE_ORDER          LSB 

#define NRF_CMD_R_REGISTER       0x00 
    #define NRF_CMD_R_REGISTER_MASK  0x1f

#define NRF_CMD_W_REGISTER       0x20
    #define NRF_CMD_W_REGISTER_MASK  0x3f

#define NRF_REGISTER_ADDY_MASK  0x1f

#define NRF_CMD_R_RX_PAYLOAD     0x61
#define NRF_CMD_W_TX_PAYLOAD     0xa0
#define NRF_CMD_FLUSH_TX         0xe1
#define NRF_CMD_FLUSH_RX         0xe2
#define NRF_CMD_REUSER_TX_PL     0xe3
#define NRF_CMD_ACTIVATE         0x50
    #define NRF_ACTIVATE_MAGIC          0x73
#define NRF_CMD_R_RX_PL_WID      0x60
#define NRF_CMD_W_ACK_PAYLOAD    0xa8
    #define NRF_CMD_W_ACK_PAYLOAD_MASK   0xaf
#define NRF_CMD_W_ACK_PAYLOAD_NO_ACK 0x58
#define NRF_CMD_NOP                  0xff

//Registers

#define NRF_REG_CONFIG      0x00
    #define NRF_PRIM_RX         (1) 
    #define NRF_PWR_UP          (1<<1) 
    #define NRF_CRCO            (1<<2) 
    #define NRF_EN_CRCO         (1<<3) 
    #define NRF_MASK_MAX_RT     (1<<4) 
    #define NRF_MASK_TX_DS      (1<<5)
    #define NFR_RX_DR           (1<<6)
    #define NFR_CONFIG_BIT_7    (1<<7)

#define NRF_REG_EN_AA       0x01
#define NRF_REG_EN_RXADDR   0x02
#define NRF_REG_SETUP_AW    0x03
#define NRF_REG_SETUP_RETR  0x04
#define NRF_REG_RF_CH       0x05
#define NRF_REG_RF_SETUP    0x06
    #define NRF_LNA_HCURR       (1)
    #define NRF_RF_PWR              (1<<2)
        #define NRF_RF_PWR_MASK     0x6
        #define NRF_POWER_18DB      0x0
        #define NRF_POWER_12DB      0x1
        #define NRF_POWER_6DB      0x2
        #define NRF_POWER_0DB       0x3
    #define NRF_RF_DR               (1<<3)
    #define NRF_PLL_LOCK            (1<<4)
    #define NRF_SETUP_RSV_MASK      0xe0 

#define NRF_REG_STATUS      0x07
    #define NRF_TX_FULL         (1)
    #define NRF_RX_P_NO         (1<<1)
        #define NRF_RX_P_NO_MASK    0xe
        #define NRF_RX_P_NO_EPY     0x7 
        #define NRF_RX_P_NO_NTU     0x6 
    #define NRF_MAX_RT          (1<<4)
    #define NRF_TX_DS           (1<<5)
    #define NRF_RX_DX           (1<<6)
    #define NRF_STATUS_BIT_7    (1<<7)

#define NRF_REG_OBSERVE_TX  0x08
#define NRF_REG_CD          0x09
#define NRF_REG_RX_ADDR_P0  0x0a
#define NRF_REG_RX_ADDR_P1  0x0b
#define NRF_REG_RX_ADDR_P2  0x0c
#define NRF_REG_RX_ADDR_P3  0x0d
#define NRF_REG_RX_ADDR_P4  0x0e
#define NRF_REG_RX_ADDR_P5  0x0f
#define NRF_REG_TX_ADDR     0x10
#define NRF_REG_RX_PW_P0    0x11
#define NRF_REG_RX_PW_P1    0x12
#define NRF_REG_RX_PW_P2    0x13
#define NRF_REG_RX_PW_P3    0x14
#define NRF_REG_RX_PW_P4    0x15
#define NRF_REG_RX_PW_P5    0x16
#define NRF_REG_FIFO_STATUS 0x17
    #define NRF_TX_REUSE        (1<<7)
    #define NRF_TX_FIFO_FULL         (1<<6)
    #define NRF_TX_EMPTY        (1<<5)
    #define NRF_FIFO_STAT_RSV_MASK  0xc   
    #define NRF_RX_FULL         (1<<1)
    #define NRF_RX_EMPTY        (1) 


#define NRF_REG_ACK_PLD     NRF_SPI_ACK_PLD
#define NRF_REG_TX_PLD      NRF_SPI_TX_PLD
#define NRF_REG_RX_PLD      NRF_SPI_RX_PLD

#define NRF_REG_DYNPD       0x1c
#define NRF_REG_FEATURE     0x1d

void nrf_open();

// Read register that is 1 byte wide
uint8_t nrf_read_register1(uint8_t r);

// Write register that is 1 byte wide
void nrf_write1(uint8_t r, uint8_t v); 

// Execute command with one byte
void nrf_command1(uint8_t r, uint8_t cmd);

// Set 5 byte address
void nrf_set_addr5(nrf_5byte_t *addy, uint8_t r);

// Get 5 byte address
void nrf_get_addr5(nrf_5byte_t *addy, uint8_t r);

// default behavior of write/status in one word
uint8_t nrf_read_status();

// Read configuration byte
uint8_t nrf_read_config();
// Read RF setup byte
uint8_t nrf_get_rf_setup();

// Activate R_RX_PL_WID, W_ACK_PAYLOAD, W_TX_PAYLOAD_NOACK
void nrf_activate();

//Set/Get TX_ADDR
void nrf_set_tx_addr(nrf_5byte_t*);
void nrf_read_tx_addr(nrf_5byte_t*);

//Set RF Power - NRF_POWER_XX macros
void nrf_set_rf_power(uint8_t power);

// Power up flag on with CRCO flag - default
void nrf_power_up();
// Power off with CRCO flag still on
void nrf_power_off();
// Unset power bit
void nrf_power_down();

// Pretty print status/registers
void nrf_print_status(uint8_t status);
void nrf_print_config(uint8_t config);
void nrf_print_addr(nrf_5byte_t*);
void nrf_print_rf_setup(uint8_t setup);

#endif
