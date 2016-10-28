#include <stdlib.h>
#include "kl25z.arch/MKL25Z4.h"
#include "frdm_uart.h"
#include "../mylib/mylib.h"


void write_uart0_va(const char* fmt, ...) {

#include <stdio.h>
    va_list ap;
    //TODO: sketchy fix
    char s[80] = {0};

    va_start(ap, fmt);
    vsnprintf(&s[0],80,fmt,ap);
    va_end(ap);

    write_uart0(&s[0]);
}

void uart0_write_n(uint32_t n) {

    int8_t *result= (int8_t*)calloc(MYLIB_MAX_DIGITS,1);
    my_utoa(result,n,10);

    for (int i=0;i<MYLIB_MAX_DIGITS;i++) {
        if (i > 127 ) { i= 32;}
            uart0_write_byte(*(result + i));
    }
}

void uart0_write_f(float f) {

    uint8_t *result= (uint8_t*)calloc(MAX_FTOA_STRING_LEN,1);
    my_ftoa(f,result);

    for (int i=0;i<MAX_FTOA_STRING_LEN;i++) {
        if (i > 127 ) { i= 32;}
            uart0_write_byte(*(result + i));
    }
}

void _newline();
void _newline() {
    if ( UART0_S1 & UART0_S1_TDRE_MASK) {
        uart0_write_byte('\r');
        uart0_write_byte('\n');
    }
}

void write_uart0(const char* c) {

    while(*c != '\0') {
        if (*c == '\n') {
            _newline();
        } else {
            uart0_write_byte(*c);
        }
        c++;
    }
}

void uart0_write_byte(const char c) {

    LOCK_CBUF
    circbuf_push(UART0_TX_BUF,c);
    UART0->C2 |= UART0_C2_TIE(1);
    UNLOCK_CBUF
}
