#ifndef __TEST_SUITE_H__
#define __TEST_SUITE_H__
#include <stdio.h>
#include <assert.h>
#include "mylib.h"

typedef char(*fpType)(void);
typedef struct {fpType test; char* name;} testType;
extern int8_t test_suite_return_code;

#define SETUP     mylib_errno=0
#define ASSERT(x) (printf("Test %s with error code %d\n", \
 (x) ? "Passed" : "[1;31;40mFailed[0;;m",mylib_errno)); \
test_suite_return_code = ((x) ? 0 : -1)

#define RETURN return test_suite_return_code

void test_print_array(const char* desc, uint8_t *a, size_t s);

#endif
