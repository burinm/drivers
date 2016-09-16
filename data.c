#include <stdlib.h>
#include "data.h"

int8_t * my_itoa(int8_t *str, int32_t data, int32_t base) {
return 0;
}

/* Works in the most basic case, no error
 * checking, no negative numbers
 */
int32_t my_atoi(int8_t *str) {
//Probably not portable
#define ASCII_0 48
#define ASCII_9 57

mylib_errno=MYLIB_ERR_OK;

int i=1;
int negative=0;
int32_t result=0;
int32_t last_result=0;
uint32_t multiplier=1;

    if (str==NULL || *str==NULL) { mylib_errno=MYLIB_ERR_NULL; return 0;}

    if (*str == '-') { negative=1; str++; }

    while(*++str) { i++; } // Fast forward to end of string
                           // so we can read it backwards

    for(str--; i>0; i--, str--) {
        if (*str >= ASCII_0 && *str <= ASCII_9) {

            /*
             *  Since the representations for the ascii
             * number characters are in order and
             * continuous, we can just use that offset
             * to get the value of that digit
            */
            result += (*str - ASCII_0) * multiplier;
            if ( result < last_result ) { //overflow

                                 //Two's compliment trick where
                                 // INT32_MIN = -INT32_MIN
                if ( negative && (result == -result) ) {
                    return result; //We know this is exactly INT32_MIN
                } else if (negative) { // This is < INT32_MIN
                            mylib_errno = MYLIB_ERR_MIN_RANGE;
                            return 0;
                } else { // This is > INT32_MAX
                    mylib_errno = MYLIB_ERR_MAX_RANGE;
                    return 0;
                }
            }

            last_result=result;
            multiplier*=10;
        } else {
            mylib_errno = MYLIB_ERR_GARBAGE_IN;
            break;
        }
    }

    if (negative) { result = -result; }

return result;
}

void dump_memory(uint8_t *start, uint32_t length) {
}

uint32_t big_to_little(uint32_t data) {
return 0;
}

uint32_t little_to_big(uint32_t data){
return 0;
}
