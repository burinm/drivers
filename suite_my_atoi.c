#include "test_suite.h"
#include "data.h"

char test_atoi_normal1(){
    int32_t result= my_atoi("123456789");
    printf("result is: %d\n",result);
    ASSERT(result == 123456789);
}

char test_ato1_zero(){
    int32_t result= my_atoi("0");
    printf("result is: %d\n",result);
    ASSERT(result == 0);
}

char test_atoi_negative(){
    int32_t result= my_atoi("-123456789");
    printf("result is: %d\n",result);
    ASSERT(result == -123456789);
}

char test_fail1(){
    ASSERT(0);
}
