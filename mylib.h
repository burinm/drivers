/* mylib.h - (c) 2016 - burin

    Main header file to include
    for my standard library
    functions
*/

#ifndef __MYLIB_H__
#define __MYLIB_H__

#include "myerrno.h"
#include "data.h"
#include "memory.h"
#include "reverse.h"
#include "circbuf.h" 
#include "circbuf_tiny.h" 
#include "printf.h"

#define MYLIB_MAX_DIGITS 33

#if 0
#ifdef FRDM_KL25Z
#pragma GCC poison printf
#endif
#endif

int printf(const char *format, ...);

/* New library modules must include the following:
 
  module.h
    extern uint8_t mylib_errno=0;
 
*/

#endif

