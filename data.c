#include <stdlib.h>
#include <stdio.h>
#include "data.h"

//Probably not portable
#define ASCII_0 48
#define ASCII_9 57

// Internal function for dump_memory
void _dump_memory(uint8_t *start, uint32_t length, uint8_t format);

int8_t * my_itoa(int8_t *str, int32_t data, int32_t base) {
mylib_errno = MYLIB_ERR_OK;
if (str == NULL) { mylib_errno = MYLIB_ERR_NULL; return 0;}
if (base < 2 || base > 255) { mylib_errno = MYLIB_ERR_ARGS; return 0;}


/*
 *   For now implement this with base <=255, one byte per digit
 *   Later see if we can't do bigger bases
 *
 *   A digit is one byte, 8 bits, so the max base = 255
 *   
 *   The longest string of digits would be base2
 *      32 bit number = 32 digits     
 *
 *   +1 digit for the sign = 33
 */

uint8_t alpha[8] = { 'a','b','c','d','e','f'};

 //Since integer will overflow when counting to 2^31
uint32_t data_hold=data;


    if (data < 0) {
        //TODO Check to make sure this is true for data == -2^31
        data_hold = -data; //because -(-2^31) == -2^31
        *str='-';
        str++;
     }

/*
 * New algorithm
 *
 * 1) Find the most significant digit of the input by multiplying
 *    the base until it doesn't fit anymore   
 * 2) Subtract each digit(n)'s value base^(n-1) as many times as we can, that
 *    is the value of digit(n).
 * 3) Move to the next less significant digit n=n-1, repeat
 *
 * Note: We will use the input string as a scratchpad, then replace the
 *       values with actual ASCII characters when we are done
 */

int highest_digit=0;
uint64_t base_pow=1;
    while ( (base_pow * base <= data_hold) ) {
        base_pow *= base;
        highest_digit++;
    }
       
for (int i=0; i<=highest_digit;i++) {
    int value_count=0;
    while (data_hold >= base_pow && (base_pow != 0 )) {
        data_hold -= base_pow;
        value_count++;
    }
    *(str + i) = value_count;
    base_pow /= base;
}

#define DATA_C_HIGH_DIGIT_NUMERAL 9
#define DATA_C_HIGH_DIGIT_ALPHA   16
    do {
            if ( *(str + highest_digit) > DATA_C_HIGH_DIGIT_NUMERAL) {
                // TODO This will currently blow up on bases > 16
                *(str + highest_digit) =
                 alpha[*(str + highest_digit) - (DATA_C_HIGH_DIGIT_NUMERAL +1)];
            } else if (  *(str + highest_digit) < DATA_C_HIGH_DIGIT_ALPHA ) {
                *(str + highest_digit) = ASCII_0 + *(str + highest_digit);
            }
    } while (highest_digit--); 
    
return 0;
}

int32_t my_atoi(int8_t *str) {
mylib_errno=MYLIB_ERR_OK;

int i=1;
int negative=0;
int32_t result=0;
int32_t last_result=0;
uint32_t multiplier=1;

    if (str==NULL || *str == 0) { mylib_errno=MYLIB_ERR_NULL; return 0;}

    if (*str == '-') { negative=1; str++; }

    while(*++str) { i++; } // Fast forward to end of string
                           // so we can read it backwards

    for(str--; i>0; i--, str--) {
        if (*str >= ASCII_0 && *str <= ASCII_9) {

            /*
             * Since the representations for the ascii
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

#define DUMP_FORMAT_HEX 0
#define DUMP_FORMAT_INT 1

#ifdef FRDM_KL25Z
void _dump_memory(uint8_t *start, uint32_t length, uint8_t format) {
}

#else
void _dump_memory(uint8_t *start, uint32_t length, uint8_t format) {
mylib_errno = MYLIB_ERR_OK;

int i=0;
int j=0;

#define MEMORY_DUMP_COL 8 
#define ASCII_MIN_PRINTABLE 32 
#define ASCII_MAX_PRINTABLE 126 

    if (format == DUMP_FORMAT_HEX) {
        printf("Address            ");
        for (i=0; i<MEMORY_DUMP_COL; i++) {
            printf("%.2x ", i); 
        }
        printf("\n\n"); 
    }

    for (i=0; i<length; i++) {
        printf("%p ",(void*)(start + i));
        for (j=0; j<MEMORY_DUMP_COL; j++) {
            if (i+j >= length) {
                if (format == DUMP_FORMAT_INT) {
                    printf("    ");
                } else { //print hex by default
                    printf("   ");
                }
            } else {
                if (format == DUMP_FORMAT_INT) {
                    printf("%.3d ",*(start+i+j));
                } else { // print hex by default
                    printf("%.2x ",*(start+i+j));
                }
            }
        }
        if (format == DUMP_FORMAT_HEX) {
            for (j=0; j<MEMORY_DUMP_COL; j++) {
                if (i+j >= length) {
                    break;
                } else {
                    if (*(start+i+j) >=ASCII_MIN_PRINTABLE \
                            && (*(start+i+j) <= ASCII_MAX_PRINTABLE)) {
                        printf("%c",*(start+i+j));
                    } else {
                        printf(".");
                    }
                }
            }
    }
            printf("\n");
            i=i+j-1;
        }
}
#endif

void dump_memory(uint8_t *start, uint32_t length) {
    _dump_memory(start, length,DUMP_FORMAT_HEX);
}

void dump_memory_int(uint8_t *start, uint32_t length) {
    _dump_memory(start,length,DUMP_FORMAT_INT);
}

uint32_t big_to_little(uint32_t data) {
    uint32_t value=0;
    value= ( 0xff000000 & data) >> 24; // shift right 3 bytes
    value+=( 0x00ff0000 & data) >> 8;  // shift right 2 bytes
    value+=( 0x0000ff00 & data) << 8;  // shift left  2 bytes
    value+=( 0x000000ff & data) << 24; // shift left 3 bytes
return value;
}

uint32_t little_to_big(uint32_t data){
/*
 * These both do the same swap,
 * however the code using them
 * is easier to understand if
 * we have both versions
 */
return big_to_little(data);
}
