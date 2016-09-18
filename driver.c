#include <stdio.h>
#include "test_suite.h"

extern testType tests_to_run[];
extern unsigned int num_tests_to_run;
int8_t test_suite_return_code;

int main() {



printf("Number tests found=%d\n",num_tests_to_run);

int i=0;
int error=0;
int passed=0;
int failed=0;

for (i=0;i<num_tests_to_run;i++) {
    printf("------------------------------\n");
    printf("Running test %s\n",tests_to_run[i].name);
    printf("------------------------------\n");
    error = (tests_to_run[i].test)();
    if (error == 0) {
        passed++;
    } else {
        failed++;
    }
    printf("\n");
}

printf("---Summary---\n");
printf("Tests passed: %d\n",passed);
printf("Tests failed: [1;31;40m%d[0;;m\n",failed);

}
