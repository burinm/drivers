#ifndef __CIRCBUF_TINY_H__
#define __CIRCBUF_TINY_H__

#include <stdint.h>

/* 255 byte circular buffer of uint8_t

    Circular buffer for size/speed contrained
     applications. Also native size for 
     8-bit platforms

    This implementation wastes one byte
     to remove the ambiguity where
     read_p = write_p could mean full
     or empty. In this implementation,
     it means empty.
*/

#define CIRCBUF_TINY_MAX   (256 - 1)

#define CIRCBUF_TINY_SIZE(c) ((c->write_i - c->read_i) & (CIRCBUF_TINY_MAX))


typedef struct {
        uint8_t write_i;
        uint8_t read_i;
        uint8_t* data;
} circbuf_tiny_t;

uint8_t circbuf_tiny_init(circbuf_tiny_t *c);
uint8_t circbuf_tiny_destroy(circbuf_tiny_t *c);
uint8_t circbuf_tiny_write(circbuf_tiny_t *c, uint8_t b);
uint8_t circbuf_tiny_read(circbuf_tiny_t *c, uint8_t *b);


#endif
