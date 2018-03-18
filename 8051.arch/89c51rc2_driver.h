/* 89c51rc2_driver.h - (c) 2016 - burin

    Platform driver for the 8051 and 89C51RC2
    microprocessor. 
*/

#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <stdint.h>
#include <at89c51ed2.h>
#include <mcs51reg.h>
#include "circbuf.h"

#define IDL_MASK 0x1
#define PD_MASK  0x2

#define INTERRUPTS_OFF \
__asm \
    clr EA \
__endasm;

#define INTERRUPTS_ON \
__asm \
    setb EA \
__endasm;

extern __xdata circbuf_t * RX_BUF;
extern __xdata circbuf_t * TX_BUF;

/* Debugging and timing functions.
    These are defined in the 8051.arch
    directory as assembly functions.
*/

// debug1_on/off - Turn port P_1 on/off for debug
void debug1_on();
void debug1_off();

// blink_p1_0 
void blink_p1_0(); 

//TODO: re-write timing functions to take argument

// wait_5us - spin for 5ms 
void wait_5us();

// wait_71ms - spin for 71ms 
void wait_71ms();

// wait_1s - spin for 1 second 
void wait_1s();

// wait_35ms - spin for 35ms
void wait_35ms();

// wait 250us - spin for 250us
void wait_250us();

// wait 212ms - spin for 212ms
void wait_212ms();

/* Main API

*/

/* debug port
    Use this macro to call dataport
*/
#ifdef DEBUG
#define DEBUGPORT(x) dataport(x)
#else
#define DEBUGPORT(x)
#endif

/* watchdog_enable
    enable system watchdog  
*/
void watchdog_enable();

/* watchdog_pet
    reset watchdog 
*/
void watchdog_pet();

/* dataport
    Write an 8 bit value to address 0xffff
    -private function
*/
void dataport(uint8_t d);

/* putchar
    Put a character in the UART buffer
*/
void putchar (char c);

/* getchar getchar_blocking
    Get a characted from the UART buffer
*/
char getchar ();

#ifndef POLLING
char getchar_blocking();
#endif

/* idle
    Put 8051 into idle mode
*/
void idle();

/* powerdown 
    Put 8051 into power down mode 
*/
void powedown();

/* reset0
    Jump to 0x000
*/
void reset0();

/* is_coldstart
    return true if POF flag set
*/
uint8_t is_coldstart();

/* oom
    Call this on a memory error
    for a blinking P1_0 port
    enters infinite loop
*/
void oom();

//Interrupt driver UART
// TODO - put turning these on/off into 
//  Makefile
#ifndef POLLING
void isr_serial(void) __interrupt (SI0_VECTOR);
#endif

//Interrupt for /EXT1 pin
//void isr_external1(void) __interrupt (IE1_VECTOR);

//Interrupt for /EXT0 pin
//void isr_external0(void) __interrupt (IE0_VECTOR);

//Interrupt for timer0
//void isr_timer0(void) __interrupt (TF0_VECTOR);

//Interrupt for any PCA event
void isr_hso(void) __interrupt (PCA_VECTOR);

/* Initialization functions

    Called to start peripherals
*/
void setup_xram();          // xram 1024i bytes, EXTRAM low
void x2_mode_on();          // double clock frequency, 6 clocks/cycle 
void x2_mode_off();         // regular clock frequency 12 clocks/cycle
void setup_soft_reset();    // enable /INT1 interrupts
void setup_int0();          // enable /INT0 interrupts
void setup_timer0();        // Setup timer 0 as 16 bit timer
void int0_on();             // /INT0 off
void int0_off();            // /INT0 on 
void int_timer0_on();       // timer0 INT on
void int_timer0_off();      // timer0 INT off
void setup_serial();        // serial port on 19200 baud
void setup_TX_RX_buffers(); // Must be called for interrupt driven UART
void setup_pca();           // Turn on modules 0,1 and thier pins
                            //  enable PCA run counter

/* pca_pwm_set_duty_cycle
 *  Set duty cycle by percent%
 *  Module 0
 */
void pca_pwm_set_duty_cycle(uint8_t duty);

/* pca_hso_set_compare
 *  Set CCAP1L/CCAP1H registers
 *  Module 1
 */
void pca_hso_set_compare(uint16_t speed);

void hso_1_on();  // turn on Module 1, high speed output mode
void hso_1_off(); // turn off Modules 1, high speed output mode          
void pwm_0_on();  // turn on Module 0, pulse width modulation
void pwm_0_off(); // turn off Module 0, pulse width modulation
#endif
