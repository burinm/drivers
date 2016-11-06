#ifndef __P123_H__
#define __P123_H__

#include <stdint.h>

typedef enum {
    NOP=0,
    BLINK_RED,
    BLINK_BLUE,
    SEND_PNG,
    PING 
} p123_cmd_e;

typedef struct {
    uint8_t cmd; //only LSByte used
    uint16_t         length;
    uint8_t        *data;
    uint32_t        checksum;
} p123_msg_t;

void p123_open();
void p123_close();
p123_msg_t* p123_alloc_msg(uint8_t m, uint16_t length);
void p123_send_cmd(p123_msg_t *c);
void p123_rcv_cmd(); 
uint32_t p123_encode_checksum(p123_msg_t *c);


#endif
