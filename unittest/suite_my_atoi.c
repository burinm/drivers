/* suite_my_atoi.c - (c) 2016 - burin */

#include "test_suite.h"
#include "data.h"

char test_atoi_null1(){
    SETUP;
    int32_t result= my_atoi(NULL);
    printf("result is: %d\n",result);
    ASSERT(mylib_errno == MYLIB_ERR_NULL);

RETURN;
}

char test_atoi_null2(){
    SETUP;
    int32_t result= my_atoi('\0');
    printf("result is: %d\n",result);
    ASSERT(mylib_errno == MYLIB_ERR_NULL);
RETURN;
}


char test_atoi_normal1(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"123456789");
    printf("result is: %d\n",result);
    ASSERT(result == 123456789);
RETURN;
}

char test_atoi_zero(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"0");
    printf("result is: %d\n",result);
    ASSERT(result == 0);
RETURN;
}

char test_atoi_1(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"1");
    printf("result is: %d\n",result);
    ASSERT(result == 1);
RETURN;
}

char test_atoi_negative(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"-123456789");
    printf("result is: %d\n",result);
    ASSERT(result == -123456789);
RETURN;
}

char test_atoi_max(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"2147483647");
    printf("result is: %d\n",result);
    ASSERT(result == INT32_MAX);
RETURN;
}

char test_atoi_min(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"-2147483648");
    printf("result is: %d\n",result);
    ASSERT(result == INT32_MIN);
RETURN;
}

char test_atoi_max_plus_one(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"2147483648");
    printf("result is: %d\n",result);
    ASSERT(mylib_errno == MYLIB_ERR_MAX_RANGE);
RETURN;
}

char test_atoi_max_plus_two(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"2147483649");
    printf("result is: %d\n",result);
    ASSERT(mylib_errno == MYLIB_ERR_MAX_RANGE);
RETURN;
}

char test_atoi_min_minus_one(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"-2147483649");
    printf("result is: %d\n",result);
    ASSERT(mylib_errno == MYLIB_ERR_MIN_RANGE);
RETURN;
}

char test_atoi_min_minus_two(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"-2147483650");
    printf("result is: %d\n",result);
    ASSERT(mylib_errno == MYLIB_ERR_MIN_RANGE);
RETURN;
}

char test_atoi_garbage(){
    SETUP;
    int32_t result= my_atoi((int8_t *)"blahblahblah");
    printf("result is: %d\n",result);
    ASSERT(mylib_errno == MYLIB_ERR_GARBAGE_IN);
RETURN;
}

char test_fail1(){
    SETUP;
    ASSERT(0);
RETURN;
}
