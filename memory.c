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

int8_t my_memzero(uint8_t *src, uint32_t length) {
mylib_errno = MYLIB_ERR_OK;
    for (int i=0; i<length; i++) {
        *(src+i)=0;
    }
return 0;
}

int8_t my_reverse(uint8_t *src, uint32_t length) {
//TODO add unittests from HW1
    reverse(src,length);
return 0;
}

int32_t my_strlen(uint8_t * src) {
    int32_t length=0;
    if (*src == '\0') { return length; }
    while (*src++) { length++; }
return length;
}
