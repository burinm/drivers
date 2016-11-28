#include "circbuf_tiny.h"
#include <stdlib.h>



uint8_t circbuf_tiny_init(circbuf_tiny_t *c) {
    if (c) {
        c->data=(uint8_t*)malloc(CIRCBUF_TINY_MAX);
        if (c->data == NULL) { return 0; }

        c->read_i=0;
        c->write_i=0;
        return 1;
    }
return 0;
}
uint8_t circbuf_tiny_destroy(circbuf_tiny_t *c) {
    if (c) {
        if (c->data) {
            free (c->data);
        }
    }
}

uint8_t circbuf_tiny_write(circbuf_tiny_t *c, uint8_t b) {
    if ( CIRCBUF_TINY_SIZE(c) < (CIRCBUF_TINY_MAX)) {
        *((c->data) + c->write_i) = b;
        c->write_i++;
        return 1;
    }
return 0;
}

uint8_t circbuf_tiny_read(circbuf_tiny_t *c, uint8_t *b) {
    if ( CIRCBUF_TINY_SIZE(c) > 0 ) {
        *b = *((c->data) + c->read_i);
        c->read_i++;
        return 1;
    }
return 0;
}
