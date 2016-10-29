#include <stdarg.h>
#include <stdio.h>
#include "mylib.h"
#ifdef FRDM_KL25Z 
    #include "../driver/frdm_uart.h"
#endif

/* classic way to convert to binary
 *
 * Shift a bit off the left side
 * Shift it back (gets filled with 0)
 * Then, if it is the same value, it must have been a 0 bit
 * If the value is differet, it must have been a 1 bit
 *
 */
void mylib_print_binary(uint32_t n) {
    if ( n == 0 ) { printf ("0\n",NULL); return; }

    uint8_t b=32; //number of bits
    while (n<<1>>1 == n) { b--; n<<=1; }
    for (;b>0;b--) {
        printf("%s", (n<<1>>1 == n) ? "0" : "1");
        n<<=1;
    }
    printf("\n",NULL);
}
          
