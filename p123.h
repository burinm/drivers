#ifndef __P123_H__
#define __P123_H__

#include <stdint.h>

typedef enum { P123_ERROR=0, P123_OK=1, P123_ALLOC_ERROR } p123_error_e;
typedef enum { P123_NO_ALLOC, P123_USR_ALLOC, P123_AUTO_ALLOC } p123_alloc_e;

typedef enum {
    NOP=0,
    BLINK_RED,
    BLINK_BLUE,
    TXT_MESSAGE,
    SEND_PNG,
    PING 
} p123_cmd_e;

typedef struct {
    uint8_t cmd; //only LSByte used
    uint16_t         length;
    uint8_t        *data;
    uint32_t        checksum;
    uint8_t         alloc_type;
} p123_msg_t;

// Interface
extern void p123_open();
extern void p123_close();
extern void p123_send_cmd(p123_msg_t *c);
extern uint8_t p123_rcv_cmd(); 

// End interface

p123_msg_t* p123_alloc_msg(uint8_t m);
void p123_attach_data(p123_msg_t* p, uint8_t *data, uint16_t length);
void p123_free_msg(p123_msg_t* m);

uint32_t p123_encode_checksum(p123_msg_t *c);

#endif
