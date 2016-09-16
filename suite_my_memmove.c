#include <string.h>
#include "test_suite.h"
#include "memory.h"

char test_my_memmove_nonoverlapping_case2(){
    SETUP;
    
    uint8_t alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    my_memmove(&alphabet[0],&alphabet[13],13);
    printf("result is: %s\n",&alphabet[0]);
    ASSERT(strcmp(&alphabet[0],"abcdefghijklmabcdefghijklm") == 0);
}

char test_my_memmove_overlapping_case2_2(){
    SETUP;
    
    uint8_t alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    my_memmove(&alphabet[13],&alphabet[0],13);
    printf("result is: %s\n",&alphabet[0]);
    ASSERT(strcmp(&alphabet[0],"nopqrstuvwxyznopqrstuvwxyz") == 0);
}

char test_my_memmove_overlapping_case4(){
    SETUP;
    
    uint8_t alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    my_memmove(&alphabet[5],&alphabet[0],10);
    printf("result is: %s\n",&alphabet[0]);
    ASSERT(strcmp(&alphabet[0],"fghijklmnoklmnopqrstuvwxyz") == 0);
}

char test_my_memmove_overlapping_case1(){
    SETUP;
    
    uint8_t alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    my_memmove(&alphabet[0],&alphabet[0],26);
    printf("result is: %s\n",&alphabet[0]);
    ASSERT(strcmp(&alphabet[0],"abcdefghijklmnopqrstuvwxyz") == 0);
}

char test_my_memmove_overlapping_case3(){
    SETUP;
    
    uint8_t alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    my_memmove(&alphabet[0],&alphabet[5],10);
    printf("result is: %s\n",&alphabet[0]);
    ASSERT(strcmp(&alphabet[0],"abcdeabcdefghijpqrstuvwxyz") == 0);
                                abcdeabcdeabcdepqrstuvwxyz
}
