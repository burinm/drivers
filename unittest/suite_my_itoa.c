/* suite_my_itoa.c - (c) 2016 - burin */

#include <stdlib.h>
#include <string.h>
#include "test_suite.h"
#include "data.h"

char test_itoa_0_base2(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,0,2);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"0") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_1_base2(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,1,2);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"1") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_0_base10(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,0,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"0") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_1_base10(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,1,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"1") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_0_base16(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,0,16);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"0") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_1_base16(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,1,16);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"1") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_12345_base10(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,12345,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"12345") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_max_binary(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,2147483647,2);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"1111111111111111111111111111111") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_max_base10(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,2147483647,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"2147483647") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_max_base16(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,2147483647,16);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"7fffffff") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}


//Negative number tests
char test_itoa_neg_1_base10(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,1,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"1") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_12345_neg(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,-12345,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"-12345") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_max_binary_neg(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,-2147483648,2);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"-10000000000000000000000000000000") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_max_base10_neg(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,-2147483648,10);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"-2147483648") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}

char test_itoa_max_base16_neg(){
    SETUP;
    
    int8_t *result= calloc(MYLIB_MAX_DIGITS,1);

    my_itoa(result,-2147483648,16);
    printf("result is: %s\n",result);
    ASSERT(strcmp((const char*)result,"-80000000") == 0);
    if (mylib_errno != MYLIB_ERR_NULL) {free (result);}
RETURN;
}
