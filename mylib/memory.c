/* memory.c - (c) 2016 - burin */

#include <stdlib.h>
#include "memory.h"

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length) {
mylib_errno = MYLIB_ERR_OK;

//TODO The best we could do is check for wild pointers
/* memmove will have 4 basic cases
 * define slength = length -1
 * 1) same region
 *      src = dst - we are done!
 * 2) non-overlapping
 *      src + slength < dst 
 *      dst + slength < src
 *          start at beginning of src, copy towards end 
 * 3) overlapping src lower in memory
 *      src + slength > dst
 *          start at end of src, copy towards beggining 
 * 4) overlapping dst lower in memory
 *      dst + slength > src //just checks if overlapping
 *      also need to check that dst < src
 *          start at beginning of src, copy towards end 
 *
 * Cases 2, and 4 use the same method
 */

    if (src == dst) { return 0; } // case 1)

    uint32_t slength = length - 1; // 0 based length
    if ( (src + slength < dst) || (dst + slength < src) // case 2)
               || ((dst + slength > src) && (dst < src)) ) // case 4)
    {
        while (length--) {
            *dst++ = *src++;
        }
    } else { // Must be case 3)
        dst= dst + slength;
        src= src + slength;
        while (length--) {
            *dst-- = *src--;
        }
    }
    
return 0;
}

/*  This routine will move memory in 4 byte blocks. 
     Both memory sections must have the same offset alignment,
     or else this can never work.
*/
int8_t my_memmove_32(uint8_t *src, uint8_t *dst, uint32_t length) {
mylib_errno = MYLIB_ERR_OK;

    if (src == dst) { return 0; } // case 1)

    uint32_t slength = length - 1; // 0 based length
    if ( (src + slength < dst) || (dst + slength < src) // case 2)
               || ((dst + slength > src) && (dst < src)) ) // case 4)
    {
        if ( ((uint32_t)dst%4) ) {
            while (length--) {
                *dst++ =*src++;
                if ( ((uint32_t)dst%4) == 0) { break; }
            }
        }

        while (length>=4) {
            *(uint32_t*)dst = *(uint32_t*)src;
            dst+=4; src+=4;
            length-=4;
        }

        while (length--) {
            *dst++ =*src++;
        }
    } else { // Must be case 3)
        dst= dst + slength;
        src= src + slength;

        if ( ((uint32_t)dst%4) ) {
            while (length--) {
                *dst++ =*src++;
                if ( ((uint32_t)dst%4) == 0) { break; }
            }
        }

        while (length>=4) {
            *(uint32_t*)dst = *(uint32_t*)src;
            dst-=4; src-=4;
            length-=4;
        }

        while (length--) {
            dst-=1; src-=1;
        }
    }
    
return 0;
}

int8_t my_memzero(uint8_t *src, uint32_t length) {
mylib_errno = MYLIB_ERR_OK;
    for (uint32_t i=0; i<length; i++) {
        *(src+i)=0;
    }
return 0;
}

int8_t my_memzero_32(uint8_t *src, uint32_t length) {
mylib_errno = MYLIB_ERR_OK;

        if ( ((uint32_t)src%4) ) {
            while (length--) {
                *src++ = 0;
                if ( ((uint32_t)src%4) == 0) { break; }
            }
        }

        while (length>=4) {
            *(uint32_t*)src = 0;
            src+=4;
            length-=4;
        }

        while (length--) {
            *src++ = 0;
        }
return 0;
}

int8_t my_reverse(uint8_t *src, uint32_t length) {
    reverse(src,length);
return 0;
}

int32_t my_strlen(uint8_t * src) {
    int32_t length=0;
    if (*src == '\0') { return length; }
    while (*src++) { length++; }
return length;
}
