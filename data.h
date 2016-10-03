#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>
#include "mylib.h"
extern uint8_t mylib_errno;

int8_t * my_itoa(int8_t *str, int32_t data, int32_t base);
int32_t my_atoi(int8_t *str);
void dump_memory(uint8_t *start, uint32_t length);
void dump_memory_int(uint8_t *start, uint32_t length);
uint32_t big_to_little(uint32_t data);
uint32_t little_to_big(uint32_t data);

/* Turn a 32 bit floating point number into a string */
#define FTOA_PRECISION             100000000
#define MAX_DIGITS_IN_32_BIT       10
#define MAX_DIGITS_IN_FRACTION     9 
#define MAX_DIGITS_SIGN            1 
#define MAX_DIGITS_NULL            1 
#define MAX_FTOA_STRING_LEN     MAX_DIGITS_IN_32_BIT + \
                                MAX_DIGITS_IN_FRACTION + \
                                MAX_DIGITS_SIGN + \
                                MAX_DIGITS_NULL
void my_ftoa(uint32_t f, uint8_t *string);


#endif
