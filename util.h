#ifndef __MYLIB_UTIL_H__
#define __MYLIB_UTIL_H__
#include <stdarg.h>

/* Print a 32 bit number out in binary. Ignore leading zeros. */
void mylib_print_binary(uint32_t n);

#ifdef FRDM_KL25Z
#define LOG0(c) \
    write_uart0(c);
#else
#define LOG0(c) \
    fprintf(stdout,"%s",c);
#endif

#ifdef FRDM_KL25Z
#define LOG1(...) \
      write_uart0_va (__VA_ARGS__)
#else
#define LOG1(...) \
      fprintf (stdout,__VA_ARGS__)
#endif

#endif
