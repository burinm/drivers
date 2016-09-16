#include "test_suite.h"
#include "data.h"

char test_atoi_normal1(){
    SETUP;
    int32_t result= my_atoi("123456789");
    printf("result is: %d\n",result);
    ASSERT(result == 123456789);
}

char test_ato1_zero(){
    SETUP;
    int32_t result= my_atoi("0");
    printf("result is: %d\n",result);
    ASSERT(result == 0);
}

char test_atoi_negative(){
    SETUP;
    int32_t result= my_atoi("-123456789");
    printf("result is: %d\n",result);
    ASSERT(result == -123456789);
}

char test_fail1(){
    SETUP;
    ASSERT(0);
}
