#include <stdio.h>
#include "reverse.h"

uint8_t reverse(uint8_t *str, int length) {

if (length < 0 || str == NULL) return -1;

uint8_t* end=str+length-1;
uint8_t* start=str;

    length/=2;
    while(length--) {
        uint8_t tmp =*start;
        *start=*end;
        *end=tmp;
        start++;
        end--;
    }

return 0;
}
