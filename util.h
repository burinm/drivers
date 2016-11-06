#ifndef __MYLIB_UTIL_H__
#define __MYLIB_UTIL_H__
#include <stdarg.h>

#ifdef BBB
    #include <stdio.h>
#endif

#ifdef X86_64
    #include <stdio.h>
#endif

/* Print a 32 bit number out in binary. Ignore leading zeros. */
void mylib_print_binary(uint32_t n);

#ifdef FRDM_KL25Z
#define LOG0(c) \
    write_uart0(c);

#define LOG1(...) \
      write_uart0_va (__VA_ARGS__)

#define LOG2X(c,x) \
    write_uart0(c); \
    uart0_write_x(x); \
    write_uart0("\n");

#define LOG2N(c,n) \
    write_uart0(c); \
    uart0_write_n(n); \
    write_uart0("\n");

#define LOG2F(c,f) \
    write_uart0(c); \
    uart0_write_f(f); \
    write_uart0("\n");

#else
#define LOG0(c) \
    fprintf(stdout,"%s",c);

#define LOG1(...) \
      fprintf (stdout,__VA_ARGS__)

#define LOG2X(c,x) \
    fprintf(stdout,"%s%x\n",c,x);

#define LOG2N(c,n) \
    fprintf(stdout,"%s%d\n",c,n);

#define LOG2F(c,f) \
    fprintf(stdout,"%s%f\n",c,f);
#endif

#ifdef LOGGING_OFF
#undef LOG0
#define LOG0(c)

#undef LOG1
#define LOG1(...)

#undef LOG2
#define LOG2X(c,x)

#undef LOG2N
#define  LOG2N(c,n)

#undef  LOG2F
#define LOG2F(c,f)
#endif

#endif
