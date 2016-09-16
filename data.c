#include "data.h"

int8_t * my_itoa(int8_t *str, int32_t data, int32_t base) {
return 0;
}

/* Works in the most basic case, no error
 * checking, no negative numbers
 */
int32_t my_atoi(int8_t *str) {
#define ASCII_0 48
#define ASCII_9 57
int i=1;
int32_t result=0;
uint32_t multiplier=1;

    while(*++str) { i++; }
    for(str--;i>0;i--,str--) {
        if (*str >= ASCII_0 && *str <=ASCII_9) {
//printf("val: %.1s %d %d\n",str, (*str-ASCII_0),   multiplier);
            result += (*str-ASCII_0) * multiplier;
            multiplier*=10;
        } else {
            mylib_errno=MYLIB_ERR_GARBAGE_IN; //need to fix this with something
            break;
        }
    }

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
