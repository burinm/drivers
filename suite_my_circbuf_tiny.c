/* suite_my_circbuf_tiny.c - (c) 2016 - burin */

#include <string.h>
#include "test_suite.h"
#include "circbuf_tiny.h"

char test_my_circbuf_tiny_empty_read(){
    SETUP;
    uint8_t b;
    uint8_t error;
    circbuf_tiny_t c;
    circbuf_tiny_init(&c);
    error = circbuf_tiny_read(&c,&b);
    printf("result is: %d\n",error);
    ASSERT(error == 0);
    circbuf_tiny_destroy(&c);
RETURN;
}

char test_my_circbuf_tiny_empty_readi_write(){
    SETUP;
    uint8_t b;
    uint8_t error;
    circbuf_tiny_t c;
    circbuf_tiny_init(&c);
    error = circbuf_tiny_read(&c,&b);
    error += circbuf_tiny_read(&c,&b);
    error += circbuf_tiny_read(&c,&b);
    printf("result is: %d\n",error);
    ASSERT(error == 0);
    circbuf_tiny_destroy(&c);
RETURN;
}

char test_my_circbuf_tiny_write1_empty(){
    SETUP;
    uint8_t b;
    uint8_t error;
    circbuf_tiny_t c;
    circbuf_tiny_init(&c);
    error = circbuf_tiny_write(&c,77);
    error = circbuf_tiny_read(&c,&b);
    printf("result is: %d\n",error);
    ASSERT(error == 1);
    error = circbuf_tiny_read(&c,&b);
    printf("result is: %d\n",error);
    ASSERT(error == 0);
    circbuf_tiny_destroy(&c);
RETURN;
}

char test_my_circbuf_tiny_init(){
    SETUP;
    circbuf_tiny_t c;
    circbuf_tiny_init(&c);
    printf("result is: %p\n",(uint8_t*)c.data);
    ASSERT(c.data != NULL);
    circbuf_tiny_destroy(&c);
RETURN;
}

char test_my_circbuf_tiny_free(){
    SETUP;
    circbuf_tiny_t c;
    circbuf_tiny_init(&c);
    printf("result is: %p\n",(uint8_t*)c.data);
    ASSERT(c.data != NULL);

    circbuf_tiny_destroy(&c);
    //Didn't crash so pass. There is no way to
    // see if free succeeded without
    // actually tearing apart the heap
RETURN;
}

char test_my_circbuf_tiny_is_full(){
    SETUP;

    uint8_t b;
    uint16_t num_writes=0;
    circbuf_tiny_t c;
    circbuf_tiny_init(&c);
    for (uint16_t i=1;i<=256;i++) {
       num_writes += circbuf_tiny_write(&c,i); 
    }
    printf("Expected num_writes == 255\n",NULL);
    printf("Result %d\n",num_writes);
    ASSERT ( num_writes == 255);

    num_writes=0;

    for (uint16_t i=1;i<=256;i++) {
       num_writes += circbuf_tiny_read(&c,&b); 
    }
    printf("Expected num_reads == 255\n",NULL);
    printf("Result %d\n",num_writes);
    ASSERT ( num_writes == 255);

        
    circbuf_tiny_destroy(&c);
RETURN;
}

char test_my_circbuf_tiny_is_empty(){
    SETUP;
    uint8_t error;

    uint8_t b;
    uint16_t num_writes=0;
    circbuf_tiny_t c;
    circbuf_tiny_init(&c);
    for (uint16_t i=0;i<10;i++) {
       error = circbuf_tiny_write(&c,i); 
       ASSERT (error == 1);
    }
    for (uint16_t i=0;i<10;i++) {
       error = circbuf_tiny_read(&c,&b); 
       ASSERT (error == 1);
    }

    error = circbuf_tiny_read(&c,&b); 
    printf("Expected error == 0\n",NULL);
    printf("Result %d\n",error);
    ASSERT ( error == 0);

RETURN;
}

char test_my_circbuf_tiny_wraparound(){
    SETUP;
    uint16_t size;

    uint8_t b;
    uint16_t num_writes=0;
    circbuf_tiny_t c;
    circbuf_tiny_init(&c);
    for (uint16_t i=0;i<100;i++) {
       circbuf_tiny_write(&c,i); 
    }
    for (uint16_t i=0;i<50;i++) {
        circbuf_tiny_read(&c,&b); 
    }

    for (uint16_t i=0;i<200;i++) {
       circbuf_tiny_write(&c,i); 
    }


    circbuf_tiny_t *c_p = &c;
    size =  CIRCBUF_TINY_SIZE(c_p);

    printf("Expected size == 250\n",NULL);
    printf("Result %d\n",size);
    ASSERT ( size == 250);

RETURN;
}


