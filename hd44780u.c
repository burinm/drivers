/* hd44780u.c - (c) 2016 - burin */

#include <stdint.h>
#include "hd44780u.h"
#include "89c51rc2_driver.h"

static uint8_t x_pos=0;
static uint8_t y_pos=0;
static uint8_t x_pos_temp=0;
static uint8_t y_pos_temp=0;

void hd44780u_cold_init() {

wait_71ms();
//unlock
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_FUNCTION | HD44780U_REG_DL;

wait_71ms();
//unlock
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_FUNCTION | HD44780U_REG_DL;

wait_250us();
//unlock
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_FUNCTION | HD44780U_REG_DL;

hd44780u_busy_wait();

//Function Set N=1, F=0
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_FUNCTION | HD44780U_REG_DL | HD44780U_REG_N;

hd44780u_busy_wait();

//Turn display off
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_DISPLAY;
hd44780u_busy_wait();

//Clear screen
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_CLEAR;
hd44780u_busy_wait();

//Entry Mode = increment
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_ENTRY| HD44780U_REG_ID;
hd44780u_busy_wait();

}

void hd44780u_warm_init() {
//TODO:
}

void  hd44780u_on() {

//Turn display on
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_DISPLAY| HD44780U_REG_D;
hd44780u_busy_wait();

}

void  hd44780u_off() {
//Turn display off 
//Not tested
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_DISPLAY;
hd44780u_busy_wait();

}

void hd44780u_busy_wait() {
while (*(__xdata uint8_t *)(HD44780U_CR) & HD44780U_REG_BF);
}

void hd44780u_put_ch(uint8_t b) {
*(__xdata uint8_t *)(HD44780U_RW) = b;
hd44780u_busy_wait();
}

//not tested
uint8_t hd44780u_get_ch() {
uint8_t b;
b = *(__xdata uint8_t *)(HD44780U_RR);
hd44780u_busy_wait();
return b;
}

void  hd44780u_goto_addr(uint8_t p) {
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_DDRAM | (p & HD44780U_REG_ADD);
hd44780u_busy_wait();
}

void  hd44780u_set_cgram_addr(uint8_t p) {
*(__xdata uint8_t *)(HD44780U_CW) = HD44780U_CMD_CGRAM | (p & HD44780U_REG_ACG);
hd44780u_busy_wait();
}

void hd44780u_cursor_next() {
        x_pos++; if (x_pos == 16) { x_pos=0; y_pos++; }
        if (y_pos == 4) { y_pos=0; }
        hd44780u_goto_xy(x_pos,y_pos);
}

void hd44780u_cursor_return() {
        x_pos=0;
        y_pos++;
        if (y_pos == 4) { y_pos=0; }
        hd44780u_goto_xy(x_pos,y_pos);
}

void hd44780u_goto_xy(uint8_t x, uint8_t y) {
uint8_t addr=0;
x_pos=x;
y_pos=y;

    if (y == 1) { addr=0x40; }
    if (y == 2) { addr=0x10; }
    if (y == 3) { addr=0x50; }

   addr+=x;
   hd44780u_goto_addr(addr); 
}

void hd44780u_push_cursor() {
    x_pos_temp=x_pos;
    y_pos_temp=y_pos;
}

void hd44780u_pop_cursor() {
    x_pos=x_pos_temp;
    y_pos=y_pos_temp;
}

void hd44780u_wipe(char c) {
uint8_t x=0;
uint8_t y=0;
uint8_t i=0;

    for (i=0;i<2;i++) {
        for (x=0;x<16;x++) {
            for (y=0;y<4;y++) {
                hd44780u_goto_xy(x,y);
                hd44780u_put_ch(i? ' ': c);
            }
        wait_35ms();
        }
    }
}

void hd44780u_fill(char c) {
uint8_t x=0;
uint8_t y=0;

    for (x=0;x<16;x++) {
        for (y=0;y<4;y++) {
            hd44780u_goto_xy(x,y);
            hd44780u_put_ch(c);
        }
    }
}

void hd44780u_fill_all(char c) {
uint8_t a;
    for (a=0;a<HD44780U_DDRAM_SIZE;a++) {
            hd44780u_goto_addr(a);
            hd44780u_put_ch(c);
    }
}

void hd44780u_put_str(char *s) {
uint8_t x=x_pos;
uint8_t y=y_pos;

    while (*s) {
        for (;y<4;y++) {
            for (;x<16;x++) {
                hd44780u_goto_xy(x,y);
                hd44780u_put_ch(*s);
                x_pos=x;
                y_pos=y;
                s++;
                if (!(*s)) { return; }
            }
            x=0;
        }
        y=0;
    }
}
