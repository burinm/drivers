#include "printf.h"

#ifdef SILENCE_PRINTF
int printf(const char *format, ...) {
}
#endif

