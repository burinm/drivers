/* test_suite.c - (c) 2016 - burin */

#include "test_suite.h"

void test_print_array(const char* desc, uint8_t *a, size_t s) {
    printf ("%s ",desc);
    for (int i=0;i<s;i++) {
        printf("%d ",*(a+i));
    }
        printf("\n",NULL);
}
