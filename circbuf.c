#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "circbuf.h"
#include "util.h"
#ifdef FRDM_KL25Z
    #include "memory.h"
#endif

#ifdef PLTFM_8051
circbuf_t *circbuf_init(uint16_t size) {
#else
circbuf_t *circbuf_init(uint32_t size) {
#endif

circbuf_t *c;

    if (size > CBUF_MAX_SIZE) { return NULL; }
    c=(circbuf_t *)malloc(sizeof(circbuf_t));
    if (!c) { return NULL; }
#ifdef FRDM_KL25Z
    c->buf=malloc(size);
    my_memzero(c->buf,size);
#else
    c->buf=(uint8_t*)malloc(size);
    if (!c->buf) { free(c); return NULL; }
    memset(c->buf,0,size);
#endif
    c->size=0;
    c->buf_size=size;
    c->last_index=(uint8_t*)((c->buf)+(size-1));
    c->head=c->buf;
    c->tail=c->buf;
    c->state=CBUF_EMPTY;

return c;
}

void circbuf_destroy(circbuf_t * c) {
    if (c->buf) { free(c->buf); }
    if (c) { free(c); }
}

void circbuf_print(circbuf_t * c) {
uint8_t *i=NULL;

    if (!c) { return; }
    for (i=c->buf;i<c->last_index +1;i++) {
        printf("%.03d ",*i);
    }
    printf("\n",NULL);
    for (i=c->buf;i<c->head;i++) {
        printf("    ",NULL);
    }
    printf("^__head\n",NULL);

    for (i=c->buf;i<c->tail;i++) {
        printf("    ",NULL);
    }
    printf("^__tail\n",NULL);
}

uint8_t circbuf_push(circbuf_t * c, uint8_t data_in) {
    if (!c) { return CBUF_ERROR; }
    if (c->state == CBUF_FULL) { return c->state; }
    c->state=CBUF_OK;

    *(c->head) = data_in;
    if (c->head == c->last_index) {
        c->head = c->buf;
    } else {
        c->head++;
    }

    c->size++;

    /* Full */
    if (c->size == c->buf_size) { c->state = CBUF_FULL; }

return c->state;
}

uint8_t circbuf_pop(circbuf_t * c, uint8_t *data_out) {
uint8_t *tail_ptr;
    if (!c) { return CBUF_ERROR; }
    if ( c->state == CBUF_EMPTY ) { return c->state; }
    c->state=CBUF_OK;

    tail_ptr=c->tail;
    *data_out = *tail_ptr;
/* Test value */
    *tail_ptr =255;

    if (c->tail == c->last_index) {
        c->tail = c->buf;
    } else {
        c->tail++;
    }

    c->size--;

    /* Empty */
    if (c->size == 0) { c->state=CBUF_EMPTY; }

return c->state;
}


#ifdef PLTFM_8051
#else
    inline
#endif
uint8_t circbuf_is_poppable(circbuf_t * c) {
    return ( c->state == CBUF_OK || c->state == CBUF_FULL) ;
}

#ifdef PLTFM_8051
#else
    inline
#endif
uint8_t circbuf_is_pushable(circbuf_t * c) {
    return ( c->state == CBUF_OK || c->state == CBUF_EMPTY) ;

}

#ifdef PLTFM_8051
#else
    inline
#endif
uint8_t circbuf_is_empty(circbuf_t * c) {
    return ( c->state == CBUF_EMPTY) ;
}

#ifdef PLTFM_8051
#else
    inline
#endif
uint8_t circbuf_is_full(circbuf_t * c) {
    return ( c->state == CBUF_FULL) ;
}

/* Private testing functions */
uint8_t* __circbuf_dump_core(circbuf_t * c) {
    return (c->buf);
}

