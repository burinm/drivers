/* printf.c - (c) 2016 - burin */
#include "printf.h"

#ifdef SILENCE_PRINTF
int myprintf(const char *format, ...) {
return 0;
}
#endif
