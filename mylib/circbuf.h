/* circbuf.h - (c) 2016 - burin

    Circular Buffer implementation (one piece of memory)

     Holds up to 2^32 8bit numbers - FIFO circular stack

     In this implementation, tail points to the current
     member to pop off the stack. Head points to the next
     empty slot. head == tail both on empty and full.
     So we use "size" to keep track of the current size
     last_index is an indirect way to keep track of allocated size 

    NOTE: this component needs revisiting for concurrency testing
*/

#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <stdint.h>


#define CBUF_MAX_SIZE   5000

typedef enum { CBUF_NOTINIT=0,
               CBUF_OK,
               CBUF_ERROR,
               CBUF_EMPTY,
               CBUF_FULL } buf_state_e;

typedef struct {
        uint8_t *buf;
#ifdef PLTFM_8051
        uint16_t size;
        uint16_t buf_size;
#else
        uint32_t size;
        uint32_t buf_size;
#endif
        uint8_t *last_index;
        uint8_t *head;
        uint8_t *tail;
        buf_state_e state;
} circbuf_t;

/*
 * Initialize circular buffer.
 * This routine take a size in bytes and allocates
 * buffer and sets all items to zero.
 *
 * Input - size in bytes
 * return - pointer to a circbuf_t
 *        - NULL if memory not allocated
 *
 */
#ifdef PLTFM_8051
circbuf_t *circbuf_init(uint16_t size);
#else
circbuf_t *circbuf_init(uint32_t size);
#endif

/*
 * Destroy circular buffer
 * This routine deletes resources and 
 * memory.
 *
 * Input - pointer to a circbuf_t
 * Return - none
 */
void circbuf_destroy(circbuf_t * c);

/*
 * Add item to stack (push)
 *
 * Input - pointer to circbuf_t 
 *  data - uint8_t
 *
 * return - CIRCBUF_ERROR on overflow
 *        - CIRCBUF_OK, item added sucessfully
 *        - CIRCBUF_NULL, null buffer passed in 
 */
uint8_t circbuf_push(circbuf_t * c, uint8_t data);

/*
 * Remove item from stack (pop)
 *
 * Input - pointer to circbuf_t 
 *  *pointer* to uint8_t
 * Output
 *  data put in *pointer*
 *
 * return - CIRCBUF_ERROR on empty
 *        - CIRCBUF_OK, item removed sucessfully
 *        - CIRCBUF_NULL, null buffer passed in 
 */
uint8_t circbuf_pop(circbuf_t * c, uint8_t *data);

/*
 * Check if stack is not empty 
 *
 * Input - pointer to circbuf_t 
 *  *pointer* to uint8_t
 *
 * return - Is stack not empty? 
 *   1 - yes
 *   0 - no 
 */
uint8_t circbuf_is_poppable(circbuf_t * c);

/*
 * Check if stack is not full 
 *
 * Input - pointer to circbuf_t 
 *  *pointer* to uint8_t
 *
 * return - Is stack not full? 
 *   1 - yes
 *   0 - no 
 */
uint8_t circbuf_is_pushable(circbuf_t * c);

/*
 * Check if stack is empty 
 *
 * Input - pointer to circbuf_t 
 *  *pointer* to uint8_t
 *
 * return - Is stack empty? 
 *   1 - yes
 *   0 - no 
 */
uint8_t circbuf_is_empty(circbuf_t * c);

/*
 * Check if stack is full 
 *
 * Input - pointer to circbuf_t 
 *  *pointer* to uint8_t
 *
 * return - Is stack full? 
 *   1 - yes
 *   0 - no 
 */
uint8_t circbuf_is_full(circbuf_t * c);




/* 
 * Print out buffer (small sizes only) for debug
 *
 *
 * Input - pointer to circbuf_t 
 *
 * return - CIRCBUF_NULL, null buffer passed in 
 *
 */
void circbuf_print(circbuf_t * c);

/* Private for testing */
uint8_t* __circbuf_dump_core(circbuf_t * c);


#endif
