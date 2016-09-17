#include <stdlib.h>
#include <string.h>
#include "test_suite.h"
#include "data.h"

char test_my_dump_memory(){
    SETUP;
    
    uint8_t memory[] = "This is memory to be printed out nicely. 0987654321" \
                       "abcdefghijklmnopqrstuvwxyz !@#$%^&*~";
    //print out string +NULL
    dump_memory(&memory[0],strlen(&memory[0]) + 1);
    ASSERT(mylib_errno == MYLIB_ERR_OK);
}

char test_my_dump_random_memory(){
    SETUP;
    
    uint8_t *memory=malloc(1000);
    dump_memory(memory,1000);
    ASSERT(mylib_errno == MYLIB_ERR_OK);
    free(memory);
}

char test_my_dump_memory_random(){
    SETUP;
    
    uint8_t *memory=malloc(256);
    for(int i=0;i<256;i++) {
        memory[i] = rand();
    }
    dump_memory(memory,256);
    ASSERT(mylib_errno == MYLIB_ERR_OK);
    free(memory);
}

char test_my_memzero(){
    SETUP;
    
    uint8_t *memory=malloc(10);
    for(int i=0;i<10;i++) {
        memory[i] = rand();
    }
    dump_memory(memory,10);
    my_memzero(memory,10);
    dump_memory(memory,10);
    for (int i=0;i<10;i++) {
        ASSERT(*(memory+i) == 0);
    }
    free(memory);
}

char test_my_strlen_1(){

    uint8_t string[] = "Hello.";
    int32_t result=my_strlen(string);
    printf("result is: %x\n",result);
    ASSERT(strlen(string) == result);
}

char test_my_strlen_0(){

    uint8_t string[] = "";
    int32_t result=my_strlen(string);
    printf("result is: %x\n",result);
    ASSERT(strlen(string) == result);
}
