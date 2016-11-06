#include "p123.h"
#include "uart.h"
#include <stdlib.h>


#include "util.h"  //debugging remove later

void p123_open() {

}

void p123_close() {
}

p123_msg_t* p123_alloc_msg(uint8_t m, uint16_t length) {
p123_msg_t* p=NULL;

    p= (p123_msg_t*)calloc(sizeof(p123_msg_t),1);
    if (p) {
                p->cmd=m;
                p->length=length;
                if (length) {
                    p->data=(uint8_t*)calloc(sizeof(uint8_t) * length,1);
                    if (p->data) { return p;}
                }
                return p;
    }

return NULL;
}

void p123_send_cmd(p123_msg_t *c) {
uint8_t i=0;
uint16_t l=0;
uint32_t checksum=0;


    checksum=p123_encode_checksum(c);
    
    uart_send_byte(c->cmd);

    l=c->length;
    uart_send_byte( (l & 0xff00) >> 8 );
    uart_send_byte( l & 0x00ff );

    l=c->length;
    if ( l != 0) {
        while (l) {
            l--;
            // MSByte first
            uart_send_byte (*(uint8_t*)((c->data) + l));
        }
    }

    for (l=0;l<4;l++) {
        uart_send_byte( (checksum & 0xff000000) >> 24);
        checksum <<= 8;
    }

}

uint32_t p123_encode_checksum(p123_msg_t *c) {
uint32_t checksum=0;
uint16_t l=c->length;

    checksum += (uint8_t)(c->cmd);
    checksum += (uint16_t)l;
    if (c->length) {
        while (l) {
            l--;
            // MSByte first
            checksum += *(uint8_t*)((c->data) + l);
        }
    }

return checksum;
}

void p123_rcv_cmd() {
uint16_t l=0;
uint16_t length=0;
uint16_t i=0;
uint32_t checksum=0;
uint32_t checksum_calculated=0;
uint8_t cmd=NOP;
uint8_t *data=NULL;
p123_msg_t * rcv_c=NULL;

    
    cmd = uart_get_byte();
    LOG2X("command = ",cmd);

    l=0;
    l = uart_get_byte();
    l <<= 8;
    l += uart_get_byte();

    length = l;
    LOG2X("length = ",length);

    data=(uint8_t*)calloc(l,1);
    if (!data) { LOG0("bork!!\n"); return;}

    for (i=0;i<length;i++) {
            l--;
            // MSByte first
            *(uint8_t*)(data + l) = uart_get_byte();
    }

    for (i=0;i<4;i++) {
        checksum += uart_get_byte();
        if (i == 3) { break; }
        checksum <<= 8;
    }

     rcv_c=(p123_msg_t*)calloc(sizeof(p123_msg_t),1);
     if (! rcv_c) { LOG0("bork2!!\n"); return;}

    rcv_c->cmd=cmd;
    rcv_c->length=length;
    rcv_c->data=data;
    
    checksum_calculated=p123_encode_checksum(rcv_c);

    if (checksum_calculated == checksum) {
        LOG2X("checksum:",checksum);
        LOG0("Hooray!\n"); 
    } else {
        LOG0("Doh!!\n");
        LOG2X("expected",checksum_calculated);
        LOG2X("got",checksum);
    }
    
    switch (cmd) {
        case BLINK_BLUE:
            LOG0("blink blink blue\n");
            break;
        default:
            LOG0("unknown command");
        }
}
