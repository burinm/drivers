#include "kl25z.arch/MKL25Z4.h"
//#include "core_cm0plus.h"
#include "frdm_firmware.h"
#include "frdm_uart.h"
#include "mylib.h"

extern volatile uint32_t stop_index;

#ifdef __cplusplus
extern "C" {
#endif
    //Should be a weak symbol in the startup files
    void PIT_IRQHandler() {

        //Timer1 - Clear Timer Interrupt flag by writing 1
        if ( PIT->CHANNEL[1].TFLG ) { 
            blue_led_toggle();
            PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
        }

        //Timer0 - Clear Timer Interrupt flag by writing 1
        if ( PIT->CHANNEL[0].TFLG ) { 
            PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
        }
    }

    void DMA0_IRQHandler() {
        // Even though this is set, I think we
        //  have to set it again to clear it.

        DMA_DSR_BCR(0) |= DMA_DSR_BCR_DONE_MASK;
        if (dma_chain) { 
            blue_led_off(); 
            dma0_memmove(DMA_CHANNEL0,
                         dma_chain_source,
                         dma_chain_dest,
                         dma_chain_size);
            dma_chain=0;
        } else {
            //Read pit0 timer
            stop_index = pit_read_timer0();
            stop_pit_timer();
        }
    }

    void UART0_IRQHandler() {
    uint8_t i=0;

    //READ

    if (UART0->C2 & UART0_C2_RIE_MASK) {
        if (UART0_S1 & UART0_S1_OR_MASK) {
            //Bummer, things were entered too fast
            // throw them away
            UART0->S1 |= UART0_S1_OR_MASK;
        } else {
            
        if ( UART0_S1 & UART0_S1_RDRF_MASK) {

            if (circbuf_is_pushable(UART0_RX_BUF)) { 
                i=UART0_D;
                circbuf_push(UART0_RX_BUF,i);
            } else {
                if (circbuf_is_full(UART0_RX_BUF)) {
                    UART0->C2 &= ~(UART0_C2_RIE_MASK);
                }
            }
        }
    }
}

    //TX
    if (UART0->C2 & UART0_C2_TIE_MASK) {
        if ( UART0_S1 & UART0_S1_TDRE_MASK) {

            // TODO: might need volatile
            uint8_t c;
            if (circbuf_is_poppable(UART0_TX_BUF)) {
                //    PTD_BASE_PTR->PCOR |= 1<<1;
                circbuf_pop(UART0_TX_BUF,&c);
                UART0_D=c;
//Bad, but needed to work.. looses last character in buffer...
                while (!(UART0_S1 & UART0_S1_TC_MASK)) {};
            } else {
                if (circbuf_is_empty(UART0_TX_BUF)) {
                    UART0->C2 &= ~(UART0_C2_TIE_MASK);
                }
            }
        }
    }


}
#ifdef __cplusplus
}
#endif
