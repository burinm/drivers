#include "nRF24L01.h"
#include "spi.h"
#include "util.h"

void nrf_config() {
    spi_set_mode(SPI_MODE_0);
    spi_set_bitorder(SPI_MSBit);
    spi_open_device();
}

uint8_t nrf_read_register(uint8_t r) {
uint8_t out=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_R_REGISTER | r);
    out = spi_readwrite_byte(SPI_CMD_DUMMY);
    spi_stop_transaction();
return out;
}

void nrf_write_1(uint8_t r, uint8_t v) {
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_W_REGISTER | r);
    (void)spi_readwrite_byte(v);
    spi_stop_transaction();
}

uint8_t nrf_read_status() {
uint8_t status=0;
    spi_start_transaction();
    status = spi_readwrite_byte(SPI_CMD_DUMMY);
    spi_stop_transaction();
return status;
}

uint8_t nrf_read_status1() {
uint8_t status=0;

    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_R_REGISTER | NRF_REG_STATUS);
    //The status byte, sent in frame 0, appears in next read...
    status = spi_readwrite_byte(SPI_CMD_DUMMY);
    spi_stop_transaction();
return status;
}

void nrf_print_status(uint8_t status) {
    LOG0("[Status]\n");
    LOG2X("NRF_RX_DX = ",status & NRF_RX_DX);
    LOG2X("NRF_TX_DS = ",status & NRF_TX_DS);
    LOG2X("NRF_MAX_RT = ",status & NRF_MAX_RT);
    LOG2X("NRF_RX_P_NO = ",(status & NRF_RX_P_NO_MASK));
    LOG2X("NRF_TX_FULL = ",status & NRF_TX_FULL);
}

uint8_t nrf_read_config() {
uint8_t config=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_R_REGISTER | NRF_REG_CONFIG);
    config = spi_readwrite_byte(SPI_CMD_DUMMY);
    spi_stop_transaction();
return config;
}

void nrf_print_config(uint8_t config) {
    LOG0("[Config]\n");
    LOG2X("MASK_RX_DR = ",config & NRF_PRIM_RX);
    LOG2X("NRF_MASK_TX_DS = ",config & NRF_MASK_TX_DS);
    LOG2X("NRF_MASK_MAX_RT = ",config & NRF_MASK_MAX_RT);
    LOG2X("NRF_EN_CRCO = ",config & NRF_EN_CRCO);
    LOG2X("NRF_CRCO = ",config & NRF_CRCO);
    LOG2X("NRF_PWR_UP = ",config & NRF_PWR_UP);
    LOG2X("NRF_PRIM_RX = ",config & NRF_PRIM_RX);
}

void nrf_activate() {
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_ACTIVATE);
    (void)spi_readwrite_byte(NRF_ACTIVATE_MAGIC);
    spi_stop_transaction();
}

void nrf_set_tx_addr(uint32_t addy) {
uint8_t i=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_W_REGISTER | NRF_REG_TX_ADDR);
    for (i=0;i<5;i++) {
        (void)spi_readwrite_byte(addy & 0xff);
        addy >>=4;
    }
    spi_stop_transaction();
}

uint32_t nrf_read_tx_addr() {
uint8_t i=0;
uint8_t temp=0;
uint8_t temp_status=0;
uint32_t addy=0;
    spi_start_transaction();
    temp_status = spi_readwrite_byte(NRF_CMD_R_REGISTER | NRF_REG_TX_ADDR);
   LOG2X("-->s",temp_status);
    for (i=0;i<5;i++) {
        temp = (spi_readwrite_byte(SPI_CMD_DUMMY)) ;
   LOG2X("-->b",temp);
        //addy |= (spi_readwrite_byte(SPI_CMD_DUMMY)) & 0xff;
    }
    spi_stop_transaction();
return addy;
}

void nfr_power_up() {
uint8_t config=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_R_REGISTER | NRF_REG_CONFIG);
    config = spi_readwrite_byte(SPI_CMD_DUMMY);
    spi_stop_transaction();

    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_W_REGISTER | NRF_REG_CONFIG);
    (void)spi_readwrite_byte(config | NRF_PWR_UP);
    spi_stop_transaction();

    //nrf_write_1(NRF_REG_CONFIG, nrf_read_register(NRF_REG_CONFIG) | NRF_PWR_UP);
}

void nfr_power_down() {
    nrf_write_1(NRF_REG_CONFIG, nrf_read_register(NRF_REG_CONFIG) & ~NRF_PWR_UP);
}

uint8_t nrf_get_rf_setup() {
uint8_t setup;
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_R_REGISTER | NRF_REG_RF_SETUP);
    setup = spi_readwrite_byte(SPI_CMD_DUMMY);
    spi_stop_transaction();
return setup;
}

void nrf_set_rf_power(uint8_t power) {
uint8_t setup;
    setup = nrf_get_rf_setup();
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_W_REGISTER | NRF_REG_RF_SETUP);
    (void)spi_readwrite_byte(setup | ((power <<1) & NRF_RF_PWR_MASK));
    spi_stop_transaction();
}

void nrf_print_rf_setup(uint8_t setup) {

    switch((setup & NRF_RF_PWR_MASK) >> 1) {
        case NRF_POWER_18DB:
            LOG0("-18dBm\n");
            break;
        case NRF_POWER_12DB:
            LOG0("-12dBm\n");
            break;
        case NRF_POWER_6DB:
            LOG0("-6dBm\n");
            break;
        case NRF_POWER_0DB:
            LOG0("0dBm\n");
            break;
        default:
            LOG0("no power found\n");
            break;
    }
 
}

#include "kl25z.arch/MKL25Z4.h"
uint8_t proffoz_nrf_status_read() {
#define NRF_CS_ENABLE() (PTC_BASE_PTR->PCOR |= 1<<8)
#define NRF_CS_DISABLE() (PTC_BASE_PTR->PSOR |= 1<<8)
#define WAIT_SPTEF ( !(SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK))
#define WAIT_SPRF ( !(SPI_S_REG(SPI0) & SPI_S_SPRF_MASK))
        uint8_t rx_ret = 0;

NRF_CS_DISABLE(); //creating edge for analyser triggering
                  //don't put into final code

        NRF_CS_ENABLE();                // Activate SPI
     while(WAIT_SPTEF);
        SPI_D_REG(SPI0) = 0xFF;
        while(WAIT_SPRF);
        rx_ret = SPI_D_REG(SPI0);

     NRF_CS_DISABLE();

        return(rx_ret);
}
