/* 89c51rc2_driver.c - (c) 2016 - burin */

#include "89c51rc2_driver.h"

extern void blink_p1_0();
extern void wait_5us();
extern void wait_71ms();
extern void wait_35ms();
extern void wait_250us();
extern void wait_1s();
extern void debug1_on();
extern void debug1_off();

#define IDL_MASK    0x1
__sfr __at (0x8F) CKCON0;

//volatile uint8_t rx_buf;
//volatile uint8_t tx_buf;

__xdata circbuf_t * RX_BUF;
__xdata circbuf_t * TX_BUF;
uint8_t woken_up; // /INT1 flag
uint8_t int0_up;  // /INT0 flag
volatile uint8_t serial_rx_up; // Serial INT RX

void setup_xram() {
    #define XRS_BITN    2     
    // XRS0 = 1, XRS1 = 1, 1K
    AUXR |= ( (0x1 | 0x2) << XRS_BITN);
}

void x2_mode_on() {
    // X2, bit 0 - 1=6 clocks per cycle 0=12 clocks
    CKCON0 |= 1;
}

void x2_mode_off() {
    // X2, bit 0 - 1=6 clocks per cycle 0=12 clocks
    CKCON0 &= ~(1);
}

//P1_0    .equ         0x90
//P1_1    .equ         0x91

#define WDTRST  0xa6
#define WDTPRG  0xa7
void watchdog_enable() {
#if 1
__asm
    clr  EA         ; disable global interrupts
    orl WDTPRG, #0x7
    mov WDTRST, #0x1e
    mov WDTRST, #0xe1
    setb EA         ; enable global interrupts
__endasm;
#endif
#if 0
    WDTPRG |= 0x7; // S2, S1, S0 =1, 2.09 second watchdog
    WDTRST=0x1e;
    WDTRST=0xe1;
#endif
}

void watchdog_pet() {
#if 0
    WDTRST=0x1e;
    WDTRST=0xe1;
#endif
#if 1
__asm
    clr  EA         ; disable global interrupts
    mov WDTRST, #0x1e
    mov WDTRST, #0xe1
    setb EA         ; enable global interrupts
__endasm;
#endif
}

void setup_soft_reset() {

__asm
            clr  EA         ; disable global interrupts
            setb IT1        ; falling edge trigger /INT1
            setb EX1        ; Turn on EXT1 interrupt
            setb EA         ; enable global interrupts
__endasm;
woken_up=0;
}

void setup_int0() {

__asm
            clr  EA         ; disable global interrupts
            setb IT0        ; falling edge trigger /INT0
            setb EX0        ; Turn on EXT0 interrupt
            setb EA         ; enable global interrupts
__endasm;
int0_up=0;
}

inline void int0_on() {
__asm
            setb EX0        ; Turn on EXT0 interrupt
__endasm;
}

inline void int0_off() {
__asm
            clr EX0        ; Turn on EXT0 interrupt
__endasm;
}

inline void int_timer0_on() {
__asm
            setb ET0        ; Turn on ET0 interrupt
__endasm;
}

inline void int_timer0_off() {
__asm
            clr ET0        ; Turn off ET0 interrupt
__endasm;
}

void setup_timer0() {
__asm
            clr TR0         ;stop timer0
            clr TF0         ;clear timer0 overflow flag

                            ; On reset TMOD == 0x0
                            ; This is software generated
                            ; timer interrupts, and the
                            ; timers are in timer mode
                            ; (v.s counting mode)

            orl TMOD, #T0_M0 ;Timer0 mode 1, 16-bit timer

            clr  EA         ; turn off interrupts
            setb ET0        ; enable timer0 overflow interrupt
            setb EA         ; turn on interrupts

            setb TR0        ; Setting this bit enables Timer0
__endasm;
}

void setup_serial() {


            serial_rx_up=0; // flag for uart receive byte
__asm
            mov SCON,#0x50  ;serial port
            orl PCON,#0x80  ;double baud

            orl TMOD,#T1_M1  ; Timer1 mode2, 8 bit, auto reload
            //19200 baud
            //mov TH1, #0xfd   ; mode2 timer reload value
            //57600 baud
            //mov TH1, #0xff   ; mode2 timer reload value
            //9600 baud
            mov TH1, #0xfa   ; mode2 timer reload value

            setb TR1        ; Setting this bit enables Timer1

#ifndef POLLING
            clr  EA         ; disable global interrupts
            setb ES         ; Turn on Seral port interrupts
            setb EA         ; enable global interrupts
#endif


__endasm;
}

void setup_TX_RX_buffers() {
    RX_BUF = (__xdata circbuf_t *)circbuf_init(500);
    if (!RX_BUF) { oom(); }
    TX_BUF = (__xdata circbuf_t *)circbuf_init(500);
    if (!TX_BUF) { oom(); }
}

void setup_pca() {
    P1_3 =1;        //Set to output
    P1_4 =1;        //Set to output

    CMOD |= CPS0;   //set PCA count pulse source = f/2
    CR=1;           //PCA Counter Run = on
}

#ifdef POLLING
void putchar (char c)
{
__asm
            clr C
            mov SBUF,dpl ;start of function arguments
checkti:
            orl C,TI
            jnc checkti ; Wait for TX ready (TI=1)
            clr TI
__endasm;
}

char getchar ()
{
__asm
            clr C
checkri:    orl C,RI
            jnc checkri
            mov dpl,SBUF ;return value goes here
            clr RI
__endasm;
}
#else // Interrupt driven UART
void putchar(char c)
{
__asm 
    clr EA
__endasm;

    if (circbuf_is_pushable(TX_BUF)) {
        circbuf_push(TX_BUF,c);
        TI=1;
    }

__asm
    setb EA
__endasm;
}

char getchar()
{
volatile char c=0;

    INTERRUPTS_OFF
    if (circbuf_is_poppable(RX_BUF)) {
        circbuf_pop(RX_BUF,&c);
    } else { c = 'U'; }

    serial_rx_up=0; 
    INTERRUPTS_ON

return c;
}

char getchar_blocking() {
char c='X';
    while(!circbuf_is_poppable(RX_BUF)); 

    INTERRUPTS_OFF
    if (circbuf_is_poppable(RX_BUF)) {
          circbuf_pop(RX_BUF,&c);
    }
    serial_rx_up=0; 
    INTERRUPTS_ON

return c;
}


#if 0 //loopback test for interrupts
void isr_serial(void) __interrupt (SI0_VECTOR)
{           
uint8_t c;
        if (RI) {
            RI=0;
             c=SBUF; SBUF=c;
         } else {
            TI=0;
        }
}
#endif

void isr_serial(void) __interrupt (SI0_VECTOR)
{           
uint8_t c='0';
    //Receive
    if (RI) {
        RI=0;
        if (circbuf_is_pushable(RX_BUF)) {
            circbuf_push(RX_BUF,SBUF);
            serial_rx_up=1;
        } else {
            serial_rx_up=2;
        }
    } 
    //Transmit
    if (TI) {
        TI=0;
            if (circbuf_is_poppable(TX_BUF)) {
                circbuf_pop(TX_BUF,&c);
                SBUF=c;
            } else { c = 'X'; }
            //while(!TI);
   }
}
#endif

void isr_external1(void) __interrupt (IE1_VECTOR)
{           
    woken_up=1;    
}

void isr_external0(void) __interrupt (IE0_VECTOR)
{           
    int0_up=1;    
}

void isr_hso(void) __interrupt (PCA_VECTOR)
{           
    //TODO: not firing...
    //P1_0 = ~(P1_0);
    if (CCF0) {
            CCF0=0;
    }

    if (CCF1) {
            CCF1=0;
        CCAP1L =  CCAP1L;
        CCAP1H += 16;
        //P1_1 = ~(P1_1);
    }

    if (CCF2) {
            CCF2=0;
    }

    if (CCF3) {
            CCF3=0;
    }

    if (CCF4) {
            CCF4=0;
    }
}

void dataport(uint8_t d) {
   *(__xdata uint16_t *)(0xffff) = d;
}

void idle() {
    PCON |= IDL_MASK;
}

void powerdown() {
    PCON |= PD_MASK;
}

#define POF 0x10
void reset0() {
__asm
    ljmp 0x0000
__endasm;

//TODO: Doesn't work
PCON &= ~(POF);
}

uint8_t is_coldstart() {
    return (PCON & POF);
}

 
void oom() {
    P1_0=1;
    for(;;) {
        blink_p1_0();
    }
}

void pca_pwm_set_duty_cycle(uint8_t duty) {
    float duty_cal= 0xff * (100-duty)/100;
    uint8_t d=(uint8_t)duty_cal;
    CCAP0H = d;
}

void pca_hso_set_compare(uint16_t speed) {
    CCAP1L = speed & 0xff;
    CCAP1H = speed >> 8;
}

void hso_1_on() {
    //Avoid unwanted match
    CCAP1L = 0x01;
    CCAP1H = 0x01;
    CCAPM1 |= (TOG | MAT | ECOM | ECCF);
    // no interrupt CCAPM1 |= (TOG | MAT | ECOM); 
}

void hso_1_off() {
    CCAPM1 &= ~(TOG | MAT | ECOM);
}

void pwm_0_on() {
    CCAPM0 |= (PWM | ECOM);
}

void pwm_0_off() {
    CCAPM0 &= ~(PWM | ECOM);
}
