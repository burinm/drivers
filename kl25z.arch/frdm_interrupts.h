/* frdm_interrupts.h - (c) 2016 - burin

    Platform driver for NXP Freedom KL25Z development board

    Interrupts
    32 bit ARM M0+ processor
*/

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

void PIT_IRQHandler();   // PIT timer interrupt handler
void UART0_IRQHandler(); // UART0 interrupts handler

#endif
