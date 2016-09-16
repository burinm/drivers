#include <stdlib.h>
#include <string.h>
#include "test_suite.h"
#include "data.h"

char test_itoa_max_binary(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,2147483647,2);
    printf("result is: %s\n",result);
    ASSERT(strcmp(result,"1111111111111111111111111111111") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}

char test_itoa_max_base10(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,2147483647,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp(result,"2147483647") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}

char test_itoa_max_base16(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,2147483647,16);
    printf("result is: %s\n",result);
    ASSERT(strcmp(result,"1fffffff") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}


