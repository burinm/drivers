#include <stdio.h>
#include "test_suite.h"
#include "../mylib/util.h"

#ifdef FRDM_KL25Z
#include "../../kl25z/kl25z.arch/MKL25Z4.h"
#include "../../kl25z/firmware.h"
#include "../../kl25z/interrupts.h"
#include "../../kl25z/uart.h"
#endif

extern testType tests_to_run[];
extern unsigned int num_tests_to_run;
int8_t test_suite_return_code;

int main(void) {

#ifdef FRDM_KL25Z
    frdm_clocks_init();
    setup_uart0(9600);
    enable_interrupts();
#endif

LOG1("Number tests found=%d\n",num_tests_to_run);

int i=0;
int error=0;
int passed=0;
int failed=0;


for (i=0;i<num_tests_to_run;i++) {
    printf("------------------------------\n",NULL);
    LOG1("Running test %s\n",tests_to_run[i].name);
    printf("------------------------------\n",NULL);
    error = (tests_to_run[i].test)();
    if (error == 0) {
        LOG0("[Passed]");
        passed++;
    } else {
        LOG0("[Failed]");
        failed++;
    }
    LOG0("\n");
}

LOG0("---Summary---\n");
LOG1("Tests passed: %d\n",passed);

#ifdef FRDM_KL25Z
//Don't print magic color characters
LOG1("Tests failed: %d",failed);
#else
LOG1("Tests failed: [1;31;40m%d[0;;m\n",failed);
#endif

#ifdef FRDM_KL25Z
    for(;;);
#endif


}
