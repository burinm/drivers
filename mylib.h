#ifndef __MYLIB_H__
#define __MYLIB_H__

#include "myerrno.h"
#include "data.h"
#include "memory.h"
#include "reverse.h"

#define MYLIB_MAX_DIGITS 33

#ifdef FRDM_KL25Z
#pragma GCC poison printf
#endif
/* New library modules must include the following:
 *
 * module.h
 *   extern uint8_t mylib_errno=0;
 *
 */

#endif

