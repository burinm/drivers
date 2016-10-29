#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#define SPI_CPOL            IDLE_LOW 
#define SPI_CPHA            SECOND_EDGE 

//Commands
#define NRF_COMMAND_WORD_ORDER      MSB 
#define NRF_DATA_BYE_ORDER          LSB 

#define NRF_CMD_R_REGISTER       0x00 
    #define NRF_CMD_R_REGISTER_MASK  0x1f

#define NRF_CMD_W_REGISTER       0x20
    #define NRF_CMD_W_REGISTER_MASK  0x3f

#define NRF_CMD_R_RX_PAYLOAD     0x61
#define NRF_CMD_W_TX_PAYLOAD     0xa0
#define NRF_CMD_FLUSH_TX         0xe1
#define NRF_CMD_FLUSH_RX         0xe2
#define NRF_CMD_REUSER_TX_PL     0xe3
#define NRF_CMD_ACTIVATE         0x50
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
#define NRF_REG_STATUS      0x07
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

#define NRF_REG_ACK_PLD     NRF_SPI_ACK_PLD
#define NRF_REG_TX_PLD      NRF_SPI_TX_PLD
#define NRF_REG_RX_PLD      NRF_SPI_RX_PLD

#define NRF_REG_DYNPD       0x1c
#define NRF_REG_FEATURE     0x1d


#endif
