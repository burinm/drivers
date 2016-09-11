#include <stdio.h>
#include "reverse.h"

char reverse(char *str, int length) {

if (length<0 || str==NULL) return -1;

char* end=str+length-1;
char* start=str;

//We could test for length > length of (str) 
// but then we would need to calculate
// string length...
//
// int actual_len=0;
// char* i=start;
// while(*i++) actual_len++;
// if (length > actual_len) return -1;

#ifdef DEBUG
printf("length %d\n",length);
printf("start 0x%x %c\n",(unsigned int)start, *start);
printf("end   0x%x %c\n",(unsigned int)end, *end);
#endif

    length/=2;
    while(length--) {
        char tmp =*start;
        *start=*end;
        *end=tmp;
        start++;
        end--;

#ifdef DEBUG
printf("start 0x%x %c\n",(unsigned int)start, *start);
printf("end   0x%x %c\n",(unsigned int)end, *end);
#endif

    }

return 0;
}
