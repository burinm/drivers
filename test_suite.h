#ifndef __TEST_SUITE_H__
#define __TEST_SUITE_H__
#include <stdio.h>
#include <assert.h>

typedef char(*fpType)(void);
typedef struct {fpType test; char* name;} testType;

#define ASSERT(x) (printf("Test %s\n", (x) ? "Passed" : "[1;31;40mFailed[0;;m"))

#endif
