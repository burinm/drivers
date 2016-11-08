#include "nRF24L01.h"
#include "spi.h"
#include "util.h"

void nrf_open() {
    spi_set_mode(SPI_MODE_0);
    spi_set_bitorder(SPI_MSBit);
    spi_open_device();
}

uint8_t nrf_read_register1(uint8_t r) {
uint8_t out=0;
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_R_REGISTER | r);
    out = spi_readwrite_byte(NRF_CMD_NOP);
    spi_stop_transaction();
return out;
}

void nrf_write1(uint8_t r, uint8_t v) {
    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_W_REGISTER | r);
    (void)spi_readwrite_byte(v);
    spi_stop_transaction();
}

void nrf_command1(uint8_t r, uint8_t cmd) {
    spi_start_transaction();
    (void)spi_readwrite_byte(r);
    (void)spi_readwrite_byte(cmd);
    spi_stop_transaction();
}

uint8_t nrf_read_status() {
uint8_t status=0;
    spi_start_transaction();
    status = spi_readwrite_byte(NRF_CMD_NOP);
    spi_stop_transaction();
return status;
}

void nrf_print_status(uint8_t status) {
    LOG0("[Status]\n");
    LOG2X("NRF_RX_DX = ",status & NRF_RX_DX);
    LOG0("\n");
    LOG2X("NRF_TX_DS = ",status & NRF_TX_DS);
    LOG0("\n");
    LOG2X("NRF_MAX_RT = ",status & NRF_MAX_RT);
    LOG0("\n");
    LOG2X("NRF_RX_P_NO = ",(status & NRF_RX_P_NO_MASK));
    LOG0("\n");
    LOG2X("NRF_TX_FULL = ",status & NRF_TX_FULL);
    LOG0("\n");
}

uint8_t nrf_read_config() {
return nrf_read_register1(NRF_REG_CONFIG); 
}

void nrf_activate() {
    nrf_command1(NRF_CMD_ACTIVATE, NRF_ACTIVATE_MAGIC);
}

void nrf_set_addr5(nrf_5byte_t *addy, uint8_t r) {
uint8_t i=0;
uint8_t *a=(uint8_t*)((uint32_t)addy + 4);

    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_W_REGISTER | r);
    for (i=0;i<5;i++) {
        (void)spi_readwrite_byte(*a);
        a--;
    }
    spi_stop_transaction();
}

void nrf_get_addr5(nrf_5byte_t *addy, uint8_t r) {
uint8_t i=0;
uint8_t *a=(uint8_t*)((uint32_t)addy +4);

    spi_start_transaction();
    (void)spi_readwrite_byte(NRF_CMD_R_REGISTER | r);
    for (i=0;i<5;i++) {
        *a= spi_readwrite_byte(NRF_CMD_NOP);
        a--;
    }
    spi_stop_transaction();
}

void nrf_set_tx_addr(nrf_5byte_t *addy) {
    nrf_set_addr5(addy, NRF_REG_TX_ADDR);
}

void nrf_read_tx_addr(nrf_5byte_t *addy) {
    nrf_get_addr5(addy, NRF_REG_TX_ADDR);
}


void nrf_power_up() {
    nrf_write1(NRF_REG_CONFIG, NRF_PWR_UP | NRF_EN_CRCO);
}

void nrf_power_off() {
    nrf_write1(NRF_REG_CONFIG, NRF_EN_CRCO);
}

void nrf_power_down() {
    nrf_write1(NRF_REG_CONFIG, nrf_read_register1(NRF_REG_CONFIG) & ~NRF_PWR_UP);
}

uint8_t nrf_get_rf_setup() {
return nrf_read_register1(NRF_REG_RF_SETUP);
}

void nrf_set_rf_power(uint8_t power) {
uint8_t setup=0;

    //clear power setting
    setup = nrf_get_rf_setup();
    nrf_write1(NRF_REG_RF_SETUP, setup & ~NRF_RF_PWR_MASK);

    //set power setting
    setup = nrf_get_rf_setup();
    nrf_write1(NRF_REG_RF_SETUP, setup | ((power <<1) & NRF_RF_PWR_MASK));
}

void nrf_print_addr(nrf_5byte_t* a) {
    LOG2X("0x",a->high);
    LOG2X("",a->low);
}

void nrf_print_config(uint8_t config) {
    LOG0("[Config]\n");
    LOG2X("MASK_RX_DR = ",config & NRF_PRIM_RX);
    LOG0("\n");
    LOG2X("NRF_MASK_TX_DS = ",config & NRF_MASK_TX_DS);
    LOG0("\n");
    LOG2X("NRF_MASK_MAX_RT = ",config & NRF_MASK_MAX_RT);
    LOG0("\n");
    LOG2X("NRF_EN_CRCO = ",config & NRF_EN_CRCO);
    LOG0("\n");
    LOG2X("NRF_CRCO = ",config & NRF_CRCO);
    LOG0("\n");
    LOG2X("NRF_PWR_UP = ",config & NRF_PWR_UP);
    LOG0("\n");
    LOG2X("NRF_PRIM_RX = ",config & NRF_PRIM_RX);
    LOG0("\n");
}


void nrf_print_rf_setup(uint8_t setup) {

    LOG2X("Reserved 7:5 :",setup & NRF_SETUP_RSV_MASK);
    LOG0("\n");
    LOG2X("NRF_PLL_LOCK :",setup & NRF_PLL_LOCK);
    LOG0("\n");
    LOG2X("NRF_RF_DR :",setup & NRF_RF_DR);
    LOG0("\n");
    LOG0("RF_POWER = ");
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
    LOG2X("NRF_LNA_HCURR :",setup & NRF_LNA_HCURR);
    LOG0("\n");
 
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
