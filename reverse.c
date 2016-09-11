#include <stdio.h>
#include "reverse.h"

char reverse(char *str, int length) {

if (length<0 || str==NULL) return -1;

char* end=str+length-1;
char* start=str;

    length/=2;
    while(length--) {
        char tmp =*start;
        *start=*end;
        *end=tmp;
        start++;
        end--;
    }

return 0;
}
