/* printf.h - (c) 2016 - burin

    Compiled in to turn off
    printf on certain platforms
*/

#ifndef __PRINTF_H__
#define __PRINTF_H__

#ifdef SILENCE_PRINTF
#define printf(...) \
      myprintf (__VA_ARGS__)

int myprintf(const char *format, ...);
#endif


#endif
