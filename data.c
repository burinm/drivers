#include <stdlib.h>
#include "data.h"

//Probably not portable
#define ASCII_0 48
#define ASCII_9 57

int8_t * my_itoa(int8_t *str, int32_t data, int32_t base) {
//TODO negative numbers
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
 */

uint8_t alpha[8] = { 'a','b','c','d','e','f'};

int counter=0;
int highest_digit=0;
int current_digit=0;
 
    /* Brute force method of counting up to base
     * in each digit. Horribly slow. Need to go
     * read up on some number theory, I know there
     * is a better way to do this
     */
    for(counter = 0; counter < data; counter++) {
        *str +=1; 
        while ( *(str + current_digit) == base) {
                *(str + current_digit + 1)+=1;
                *(str + current_digit)=0;
                current_digit++;
                if (current_digit > highest_digit) {
                     highest_digit=current_digit;
                 }
        }
        current_digit=0;
    }

   reverse(str, highest_digit + 1);  

    do {
            if ( *(str + highest_digit) > 9) {
                *(str + highest_digit) = alpha[*(str + highest_digit) - 10];
            } else {
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
mylib_errno = MYLIB_ERR_OK;

int i=0;
int j=0;

#define MEMORY_DUMP_COL 16
#define ASCII_MIN_PRINTABLE 32 
#define ASCII_MAX_PRINTABLE 126 

    printf("Address  ");
    for (i=0; i<MEMORY_DUMP_COL; i++) {
        printf("%.2x ", i); 
    }
    printf("\n\n"); 

    for (i=0; i<length; i++) {
        printf("%.8x ",(uint8_t *)start+i);
        for (j=0; j<MEMORY_DUMP_COL; j++) {
            if (i+j >= length) {
                printf("   ");
            } else {
                printf("%.2x ",*(start+i+j));
            }
        }
        printf(" ");
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
        printf("\n");
        i=i+j-1;
    }
}

uint32_t big_to_little(uint32_t data) {
    uint32_t value=0;
    value= ( 0xff000000 & data) >> 24;
    value+=( 0x00ff0000 & data) >> 8;
    value+=( 0x0000ff00 & data) << 8;
    value+=( 0x000000ff & data) << 24;
return value;
}

uint32_t little_to_big(uint32_t data){
/*
 * These both do the same swap,
 * however the code using them
 * is easier to understand if
 * we have both
 */
return big_to_little(data);
}
