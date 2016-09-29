#include <stdlib.h>
#include <stdio.h>
#include "circbuf.h"

circbuf_t *circbuf_init(uint32_t size) {
circbuf_t *c;

    c=malloc(sizeof(circbuf_t));
    c->buf=calloc(size,0);
    c->size=0;
    c->last_index=size-1;
    c->head=0;
    c->tail=0;
    c->state=CBUF_OK;

return c;
}

void circbuf_destroy(circbuf_t * c) {
    if (c->buf) { free(c->buf); }
    if (c) { free(c); }
}

void circbuf_print(circbuf_t * c) {
    if (!c) { return; }
    for (int i=0;i<c->last_index +1;i++) {
        printf("%.03d ",*((c->buf)+i));
    }
    printf("\n");
    for (int i=0;i<c->head;i++) {
        printf("    ");
    }
    printf("^__head\n");

    for (int i=0;i<c->tail;i++) {
        printf("    ");
    }
    printf("^__tail\n");
}

uint8_t circbuf_push(circbuf_t * c, uint8_t data) {
    if (!c) { return CBUF_ERROR; }
    if (c->state == CBUF_FULL) { return c->state; }
    c->state=CBUF_OK;

    *((c->buf) + c->head) = data;
    if (c->head == c->last_index) {
        c->head = 0;
    } else {
        c->head++;
    }

    c->size++;

    /* Full */
    if (c->size == c->last_index + 1) { c->state = CBUF_FULL; }

return c->state;
}

uint8_t circbuf_pop(circbuf_t * c, uint8_t *data) {
    if (!c) { return CBUF_ERROR; }
    if ( c->state == CBUF_EMPTY ) { return c->state; }
    c->state=CBUF_OK;

    uint8_t *tail_ptr=((c->buf) + c->tail);
    *data = *tail_ptr;
    *tail_ptr =255;

    if (c->tail == c->last_index) {
        c->tail = 0;
    } else {
        c->tail++;
    }

    c->size--;

    /* Empty */
    if (c->size == 0) { c->state=CBUF_EMPTY; }

return c->state;
}


uint8_t circbuf_is_poppable(circbuf_t * c) {
    return ( c->state == CBUF_OK || c->state == CBUF_FULL) ;
}

uint8_t circbuf_is_pushable(circbuf_t * c) {
    return ( c->state == CBUF_OK || c->state == CBUF_EMPTY) ;

}

