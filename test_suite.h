#ifndef __TEST_SUITE_H__
#define __TEST_SUITE_H__
#include <stdio.h>
#include <assert.h>
#include "mylib.h"

typedef char(*fpType)(void);
typedef struct {fpType test; char* name;} testType;

#define SETUP     mylib_errno=0;
#define ASSERT(x) (printf("Test %s with error code %d\n", \
 (x) ? "Passed" : "[1;31;40mFailed[0;;m",mylib_errno))

#endif
