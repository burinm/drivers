#include <stdlib.h>
#include <string.h>
#include "test_suite.h"
#include "data.h"

char test_my_ftoa_1(){
    SETUP;

    uint8_t *string=calloc(MAX_FTOA_STRING_LEN,1);
    
    float f =-7.5;
    my_ftoa(f,string);
    printf("result is: %s\n",string);
    ASSERT(strcmp((const char*)string, "-7.50000000") == 0);

    free (string);
RETURN;
}
