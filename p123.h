#ifndef __P123_H__
#define __P123_H__

#include <stdint.h>

typedef enum { P123_ERROR=0, P123_OK=1, P123_ALLOC_ERROR } p123_error_e;
typedef enum { P123_NO_ALLOC, P123_USR_ALLOC, P123_AUTO_ALLOC } p123_alloc_e;

//Messages
typedef enum {
    P123_MSG_NOP=0,
    P123_MSG_BLINK_RED,
    P123_MSG_BLINK_BLUE,
    P123_MSG_BLINK_BLUE_OFF,
    P123_MSG_GREEN_ON,
    P123_MSG_GREEN_OFF,
    P123_MSG_TXT_MESSAGE,
    P123_MSG_SEND_PNG,
    P123_MSG_PING 
} p123_cmd_e;

typedef struct {
    uint8_t cmd;
    uint16_t        length;
    uint8_t         *data;
    uint32_t        checksum;
    uint8_t         alloc_type;
} p123_msg_t;

// Interface
extern void p123_open();
extern void p123_close();
extern void p123_send_cmd(p123_msg_t *c);
extern uint8_t p123_rcv_cmd(); 

// End interface

// Alloates new message structure
p123_msg_t* p123_alloc_msg(uint8_t m);

// Attach message data, user tracks memory
void p123_attach_data(p123_msg_t* p, uint8_t *data, uint16_t length);

// Free message structure
void p123_free_msg(p123_msg_t* m);

// Internal checksum function
uint32_t p123_encode_checksum(p123_msg_t *c);

#endif
