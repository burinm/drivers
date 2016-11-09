#include "p123.h"
#include "uart.h"
#include <stdlib.h>


#include "util.h"  //debugging remove later

void p123_open() {

}

void p123_close() {
}

p123_msg_t* p123_alloc_msg(uint8_t m) {
p123_msg_t* p=NULL;

    p= (p123_msg_t*)calloc(sizeof(p123_msg_t),1);
    if (p) {
                p->cmd=m;
                p->length=0;
                p->data=NULL;
                p->checksum=0x78787878;
                p->alloc_type=P123_NO_ALLOC;
                return p;
    }

return NULL;
}

void p123_attach_data(p123_msg_t* p, uint8_t *data, uint16_t length) {
    if (p) {
        p->alloc_type=P123_USR_ALLOC;
        if (data) {
        p->data=data;
        p->length=length;
        }
    }
}

void p123_free_msg(p123_msg_t* m) {
    if (m) {
        if ( m->alloc_type == P123_AUTO_ALLOC ) {
            if (m->data) {
                free(m);
            }
        }
        free (m);
    }
}

void p123_send_cmd(p123_msg_t *c) {
uint16_t l=0;
uint32_t checksum=0;


    checksum=p123_encode_checksum(c);
    
    uart_send_byte(c->cmd);
LOG2X("command>",c->cmd);

    l=c->length;
    uart_send_byte( (l & 0xff00) >> 8 );
    uart_send_byte( l & 0x00ff );
LOG2X("length>",l);

    l=c->length;
    if ( l != 0) {
        while (l) {
            l--;
            // MSByte first
            uart_send_byte (*(uint8_t*)((c->data) + l));
LOG2X(">",*(uint8_t*)((c->data) + l));
        }
    }

LOG2X("checksum>",checksum);
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

uint8_t p123_rcv_cmd(p123_msg_t * rcv_c) {
uint16_t l=0;
uint16_t length=0;
uint16_t i=0;
uint32_t checksum=0;
uint32_t checksum_calculated=0;
uint8_t cmd=P123_MSG_NOP;
uint8_t *data=NULL;
uint8_t csum=0;

    
    if (! rcv_c) { LOG0("bork2!!\n"); return P123_ALLOC_ERROR;}

    cmd = uart_get_byte();
    LOG2X("[command: ",cmd); LOG0(" ]\n");

    l=0;
    l = uart_get_byte();
    l <<= 8;
    l += uart_get_byte();

    length = l;
    LOG2X("length:0x",length); LOG0("\n");

    data=(uint8_t*)calloc(l,1);
    if (!data) { LOG0("bork!!\n"); return P123_ALLOC_ERROR;}
    rcv_c->alloc_type=P123_AUTO_ALLOC;

    for (i=0;i<length;i++) {
            l--;
            // MSByte first
            *(uint8_t*)(data + l) = uart_get_byte();
            LOG2X(":",*(uint8_t*)(data + l));
    }

    for (i=0;i<4;i++) {
        csum = uart_get_byte();
        LOG2X("(c):",csum);
        checksum += csum;
        if (i == 3) { break; }
        checksum <<= 8;
    }

    LOG0("\n");

    rcv_c->cmd=cmd;
    rcv_c->length=length;
    rcv_c->data=data;
    
    checksum_calculated=p123_encode_checksum(rcv_c);

    if (checksum_calculated == checksum) {
        LOG2X("checksum: ",checksum);
        LOG0(" is correct\n"); 
        LOG0("\n");
    } else {
        LOG0("Checksum failed!\n");
        LOG2X("expected: ",checksum_calculated);
        LOG0("\n");
        LOG2X("got: ",checksum);
        LOG0("\n");
    }
    
return P123_OK;
}
