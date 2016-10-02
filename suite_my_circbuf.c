#include <string.h>
#include "test_suite.h"
#include "circbuf.h"

char test_my_circbuf_init(){
    SETUP;
    circbuf_t *c;
    c=circbuf_init(10);
    printf("result is: %p\n",(uint8_t*)c);
    ASSERT(c != NULL);
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_init2(){
    SETUP;
    uint8_t *buf;
    circbuf_t *c;
    c=circbuf_init(10);
    buf=__circbuf_dump_core(c);
    for (int i=0;i<10;i++) {
        ASSERT (*(buf+i) ==0);
    }
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_push1(){
    SETUP;

    uint8_t expected[]={ 1,2,3,4,5,6,7,8,9,10 };
    uint8_t *buf;
    circbuf_t *c;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
    test_print_array("Expected",&expected[0],10);
    buf=__circbuf_dump_core(c);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected[0],10) == 0);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_push_pop1(){
    SETUP;

    uint8_t expected[]={ 255,255,255,255,255,255,255,255,255,255 };
    uint8_t out;
    uint8_t *buf;
    circbuf_t *c;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
    for (uint8_t i=1;i<=10;i++) {
       circbuf_pop(c,&out); 
    }
    test_print_array("Expected",&expected[0],10);
    buf=__circbuf_dump_core(c);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected[0],10) == 0);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_push_pop2(){
    SETUP;

    uint8_t expected[]={ 1,2,3,4,5,6,7,8,9,10 };
    uint8_t out;
    circbuf_t *c;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
    for (uint8_t i=1;i<=10;i++) {
       printf("Expected %d\n",i);
       circbuf_pop(c,&out); 
        ASSERT (out == i);
       printf("result %d\n",out);
    }
        
    if (c) { circbuf_destroy(c); }
RETURN;
}



char test_my_circbuf_push_overflow(){
    SETUP;

    uint8_t expected[]={ 1,2,3,4,5,6,7,8,9,10 };
    uint8_t *buf;
    circbuf_t *c;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=20;i++) {
       circbuf_push(c,i); 
    }
    test_print_array("Expected",&expected[0],10);
    buf=__circbuf_dump_core(c);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected[0],10) == 0);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_pop_overflow(){
    SETUP;

    uint8_t expected[]={ 255,255,255,255,255,255,255,255,255,255 };
    uint8_t out;
    uint8_t *buf;
    circbuf_t *c;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
    for (uint8_t i=1;i<=20;i++) {
       circbuf_pop(c,&out); 
    }
    test_print_array("Expected",&expected[0],10);
    buf=__circbuf_dump_core(c);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected[0],10) == 0);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}





