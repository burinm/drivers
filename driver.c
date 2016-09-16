#include <stdio.h>
#include "test_suite.h"

extern testType tests_to_run[];
extern unsigned int num_tests_to_run;

int main() {



printf("Number tests found=%d\n",num_tests_to_run);

int i=0;
for (i=0;i<num_tests_to_run;i++) {
int error;
    printf("Running test %s\n",tests_to_run[i].name);
    error = (tests_to_run[i].test)();
}


}
