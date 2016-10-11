#include <stdlib.h>
#include <string.h>
#include "test_suite.h"
#include "data.h"

char test_my_ftoa_example(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f =-7.5;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strcmp((const char*)string, "-7.50000000") == 0);

    free (string);
RETURN;
}

char test_my_ftoa_bigish(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f=800000;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strcmp((const char*)string, " 800000.0000000") == 0);

    free (string);
RETURN;
}

char test_my_ftoa_0(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f =0;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strcmp((const char*)string, " 0.0000000") == 0);

    free (string);
RETURN;
}

char test_my_ftoa_1(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f=1;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strcmp((const char*)string, " 1.0000000") == 0);

    free (string);
RETURN;
}

char test_my_ftoa_neg_1(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f=-1;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strcmp((const char*)string, "-1.0000000") == 0);

    free (string);
RETURN;
}

/* Just check for leading 0s and decimal point */
char test_my_ftoa_one_tenth(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f=.1;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strncmp((const char*)string, " 0.",3) == 0);

    free (string);
RETURN;
}

char test_my_ftoa_one_hundredth(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f=.01;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strncmp((const char*)string, " 0.0",4) == 0);

    free (string);
RETURN;
}

char test_my_ftoa_one_thousandth(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f=.001;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strncmp((const char*)string, " 0.00",5) == 0);

    free (string);
RETURN;
}
