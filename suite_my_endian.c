#include <string.h>
#include "test_suite.h"
#include "data.h"

char test_my_big_to_little_1(){
    SETUP;
    
    uint32_t result=big_to_little(0xabcdef12); 
    printf("result is: %x\n",result);
    ASSERT(result == 0x12efcdab);
RETURN;
}

char test_my_big_to_little_2(){
    SETUP;
    
    uint32_t result=big_to_little(0x0); 
    printf("result is: %x\n",result);
    ASSERT(result == 0x0);
RETURN;
}

char test_my_little_to_big_1(){
    SETUP;
    
    uint32_t result=big_to_little(0xabcdef12); 
    printf("result is: %x\n",result);
    ASSERT(result == 0x12efcdab);
RETURN;
}

char test_my_little_to_big_2(){
    SETUP;
    
    uint32_t result=big_to_little(0x0); 
    printf("result is: %x\n",result);
    ASSERT(result == 0x0);
RETURN;
}


