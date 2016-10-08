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

char test_my_circbuf_alloc_too_much(){
    SETUP;
    circbuf_t *c;
    c=circbuf_init(5001);
    printf("result is: %p\n",(uint8_t*)c);
    ASSERT(c == NULL);
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_free(){
    SETUP;
    circbuf_t *c;
    c=circbuf_init(10);
    printf("result is: %p\n",(uint8_t*)c);
    ASSERT(c != NULL);
    if (c) { circbuf_destroy(c); }
    //Didn't crash so pass. There is no way to
    // see if free succeeded without
    // actually tearing apart the heap
RETURN;
}

char test_my_circbuf_is_full(){
    SETUP;

    circbuf_t *c;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
    uint8_t result=circbuf_is_pushable(c);
    printf("Expected circbuf_is_pushable == 0\n",NULL);
    printf("Result %d\n",result);
    ASSERT ( result == 0);

    result=circbuf_is_poppable(c);
    printf("Expected circbuf_is_poppable == 1\n",NULL);
    printf("Result %d\n",result);
    ASSERT ( result == 1);

    uint32_t size=c->size;
    printf("Expected size == 10\n",NULL);
    printf("Result %d\n",size);
    ASSERT ( size == 10);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_is_empty(){
    SETUP;

    circbuf_t *c;
    uint8_t d;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
    for (uint8_t i=1;i<=10;i++) {
       circbuf_pop(c,&d); 
    }
    uint8_t result=circbuf_is_pushable(c);
    printf("Expected circbuf_is_pushable == 1\n",NULL);
    printf("Result %d\n",result);
    ASSERT ( result == 1);

    result=circbuf_is_poppable(c);
    printf("Expected circbuf_is_poppable == 0\n",NULL);
    printf("Result %d\n",result);
    ASSERT ( result == 0);

    uint32_t size=c->size;
    printf("Expected size == 0\n",NULL);
    printf("Result %d\n",size);
    ASSERT ( size == 0);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_is_half_full(){
    SETUP;

    circbuf_t *c;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=5;i++) {
       circbuf_push(c,i); 
    }
    uint8_t result=circbuf_is_pushable(c);
    printf("Expected circbuf_is_pushable == 1\n",NULL);
    printf("Result %d\n",result);
    ASSERT ( result == 1);

    result=circbuf_is_poppable(c);
    printf("Expected circbuf_is_poppable == 1\n",NULL);
    printf("Result %d\n",result);
    ASSERT ( result == 1);

    uint32_t size=c->size;
    printf("Expected size == 5\n",NULL);
    printf("Result %d\n",size);
    ASSERT ( size == 5);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_wraparound(){
    SETUP;

    uint8_t expected[]={ 11,12,13,255,255,6,7,8,9,10 };
    uint8_t *buf;
    circbuf_t *c;
    uint8_t d;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
    for (uint8_t i=1;i<=5;i++) {
       circbuf_pop(c,&d); 
    }
    for (uint8_t i=11;i<=13;i++) {
       circbuf_push(c,i); 
    }
circbuf_print(c);

    test_print_array("Expected",&expected[0],10);
    buf=__circbuf_dump_core(c);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected[0],10) == 0);

    circbuf_push(c,88);
circbuf_print(c);
    buf=__circbuf_dump_core(c);
    uint8_t expected2[]={ 11,12,13,88,255,6,7,8,9,10 };
    test_print_array("Expected",&expected2[0],10);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected2[0],10) == 0);

    circbuf_pop(c,&d);
circbuf_print(c);
    printf("Result %d \n",d);
    ASSERT (d == 6);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_wraparound_boundry(){
    SETUP;

    uint8_t *buf;
    circbuf_t *c;
    uint8_t d;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
circbuf_print(c);

    circbuf_pop(c,&d); 
circbuf_print(c);

    circbuf_push(c,88);
circbuf_print(c);
    buf=__circbuf_dump_core(c);
    uint8_t expected2[]={ 88,2,3,4,5,6,7,8,9,10 };
    test_print_array("Expected",&expected2[0],10);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected2[0],10) == 0);

    circbuf_pop(c,&d);
circbuf_print(c);
    printf("Result %d \n",d);
    ASSERT (d == 2);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_wraparound_boundry2(){
    SETUP;

    circbuf_t *c;
    uint8_t d;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
circbuf_print(c);

    circbuf_pop(c,&d); 
circbuf_print(c);
    printf("Expected 1\n",NULL);
    printf("Result %d \n",d);
    ASSERT (d == 1);

    circbuf_pop(c,&d);
circbuf_print(c);
    printf("Expected 2\n",NULL);
    printf("Result %d \n",d);
    ASSERT (d == 2);

    circbuf_pop(c,&d);
circbuf_print(c);
    printf("Expected 3\n",NULL);
    printf("Result %d \n",d);
    ASSERT (d == 3);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_wraparound_boundry2_minus_1(){
    SETUP;

    circbuf_t *c;
    uint8_t d;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=9;i++) {
       circbuf_push(c,i); 
    }
circbuf_print(c);

    circbuf_pop(c,&d); 
circbuf_print(c);
    printf("Expected 1\n",NULL);
    printf("Result %d \n",d);
    ASSERT (d == 1);

    circbuf_pop(c,&d);
circbuf_print(c);
    printf("Expected 2\n",NULL);
    printf("Result %d \n",d);
    ASSERT (d == 2);

    circbuf_pop(c,&d);
circbuf_print(c);
    printf("Expected 3\n",NULL);
    printf("Result %d \n",d);
    ASSERT (d == 3);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_wraparound_boundry3(){
    SETUP;

    uint8_t *buf;
    circbuf_t *c;
    uint8_t d;
    c=circbuf_init(10);
    for (uint8_t i=1;i<=10;i++) {
       circbuf_push(c,i); 
    }
circbuf_print(c);

    circbuf_pop(c,&d); 
circbuf_print(c);

    circbuf_pop(c,&d);
circbuf_print(c);
    printf("Expected 2\n",NULL);
    printf("Result %d \n",d);
    ASSERT (d == 2);

    circbuf_pop(c,&d);
circbuf_print(c);
    printf("Expected 3\n",NULL);
    printf("Result %d \n",d);
    ASSERT (d == 3);

    for (uint8_t i=100;i<=120;i++) {
       circbuf_push(c,i); 
    }

    buf=__circbuf_dump_core(c);
    uint8_t expected2[]={ 100,101,102,4,5,6,7,8,9,10 };
    test_print_array("Expected",&expected2[0],10);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected2[0],10) == 0);
circbuf_print(c);
        
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

    uint8_t error=0;
    error=circbuf_is_pushable(c);
    printf("Expected ERROR pushable == 0\n",NULL);
    ASSERT (error == 0);
    printf("Result %d\n",error);

    uint32_t size=c->size;
    printf("Expected size == 10\n",NULL);
    printf("Result %d\n",size);
    ASSERT ( size == 10);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_pop_underflow(){
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

    uint8_t error=0;
    error=circbuf_is_poppable(c);
    printf("Expected ERROR popable == 0\n",NULL);
    ASSERT (error == 0);
    printf("Result %d\n",error);

    uint32_t size=c->size;
    printf("Expected size == 0\n",NULL);
    printf("Result %d\n",size);
    ASSERT ( size == 0);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}

char test_my_circbuf_push_pop3(){
    SETUP;

    uint8_t expected1[]={ 255,255,255,255,255,255,70,71,72,255 };
    uint8_t expected2[]={ 255,255,255,255,255,255,255,255,255,255 };
    
    uint8_t out=0;
    uint8_t *buf;
    circbuf_t *c;
    c=circbuf_init(10);

for (int j=1;j<20;j++) {
        if ( circbuf_is_pushable(c) ) {
        circbuf_push(c,j);
        printf ("push a %d\n",j);
        }
}

if ( circbuf_is_poppable(c) ) {
    circbuf_pop(c,&out);
    printf("Popped a \"%d\"\n",out);
}

if ( circbuf_is_pushable(c) ) {
    circbuf_push(c,88);
    printf("Pushed a \"%d\"\n",88);
}


for (int i=0;i<20;i++) {
    if ( circbuf_is_poppable(c) ) {
        circbuf_pop(c,&out);
        printf("Popped a \"%d\"\n",out);
    }
}

for (int j=50;j<55;j++) {
        if ( circbuf_is_pushable(c) ) {
        circbuf_push(c,j);
        printf ("push a %d\n",j);
        }
}

for (int i=0;i<4;i++) {
    if ( circbuf_is_poppable(c) ) {
        circbuf_pop(c,&out);
        printf("Popped a \"%d\"\n",out);
    }
}

for (int i=0;i<20;i++) {
    if ( circbuf_is_poppable(c) ) {
        circbuf_pop(c,&out);
        printf("Popped a \"%d\"\n",out);
    }
}

circbuf_print(c);
for (int j=70;j<73;j++) {
        if ( circbuf_is_pushable(c) ) {
        circbuf_push(c,j);
        printf ("push a %d\n",j);
        }
}
circbuf_print(c);


    test_print_array("Expected",&expected1[0],10);
    buf=__circbuf_dump_core(c);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected1[0],10) == 0);

for (int i=0;i<20;i++) {
    if ( circbuf_is_poppable(c) ) {
        circbuf_pop(c,&out);
        printf("Popped a \"%d\"\n",out);
    }
}

    test_print_array("Expected",&expected2[0],10);
    buf=__circbuf_dump_core(c);
    test_print_array("Result  ",buf,10);
    ASSERT (strncmp((const char*)buf,(const char*)&expected2[0],10) == 0);
        
    if (c) { circbuf_destroy(c); }
RETURN;
}




