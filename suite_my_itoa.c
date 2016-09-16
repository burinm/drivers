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
    ASSERT(strcmp(result,"7fffffff") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}

char test_itoa_max_0_base16(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,0,16);
    printf("result is: %s\n",result);
    ASSERT(strcmp(result,"0") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}

//Negative number tests
char test_itoa_12345_neg(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,-12345,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp(result,"-12345") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}

char test_itoa_max_binary_neg(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,-2147483648,2);
    printf("result is: %s\n",result);
    ASSERT(strcmp(result,"-10000000000000000000000000000000") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}

char test_itoa_max_base10_neg(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,-2147483648,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp(result,"-2147483648") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}

char test_itoa_max_base16_neg(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,-2147483648,16);
    printf("result is: %s\n",result);
    ASSERT(strcmp(result,"-80000000") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
}
