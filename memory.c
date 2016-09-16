#include "memory.h"

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length) {
mylib_errno = MYLIB_ERR_OK;

//TODO if > DATA_MAX error...
//TODO  wild pointers?
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

    if (src == dst) { return 0; } //case 1)

    uint32_t slength = length - 1; // 0 based length
    if ( (src + slength < dst) || (dst + slength < src) //case 2)
               | ((dst + slength > src) && (dst < src)) ) //case 4)
    {
        while (length--) {
            *dst++ = *src++;
        }
    } else { //Must be cast 3)
        dst= dst + slength;
        src= src + slength;
        while (length --) {
            *dst-- = *src--;
        }
    }
    
return 0;
}

int8_t my_memzero(uint8_t *src, uint32_t length) {
return 0;
}

int8_t my_reverse(uint8_t *src, uint32_t length) {
//TODO add unittests from HW1 to here
    reverse(src,length);
return 0;
}


