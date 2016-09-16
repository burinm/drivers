#include "test_suite.h"
#include "data.h"

char test_itoa_null1(){
    SETUP;
    
    int8_t *result= malloc(MYLIB_MAX_DIGITS);

    my_itoa(result,2147483647,2);
    printf("result is: %s\n",result);
    ASSERT(mylib_errno == MYLIB_ERR_OK);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}

