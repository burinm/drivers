#include "memtest8.h"

//#define MEM_READ_ADDR(x)    *(uint8_t*)(x)   

#define MEM_PAT     (0xaa)
#define MEM_PAT_N   (0x55)
uint8_t mem_addr_test( void(*write_f)(uint16_t, uint8_t),
                      uint8_t(*read_f)(uint16_t),
                      uint32_t addr) {
int8_t bit_count;
int8_t i;
int8_t j;
int8_t k;
uint16_t a;
uint32_t bits;
uint8_t read;

//Find highest bit
bit_count=32;
bits=1;
while (bit_count--) {
    if ( (bits<<bit_count) & addr) { break;}
}

printf("-->%d bits\n",bit_count);

bit_count--;
j=bit_count;

    while(j>-2) {
        i=bit_count;
        while(i>-2) {
            a = 1<<i;
            write_f(a,MEM_PAT);
            printf("%04x->0x%x  ",a, MEM_PAT);
            if ((i % 0x4) == 0) { printf("\n");}
            i--;
        }

        a = 1<<j;
        write_f(a,MEM_PAT_N);
        printf("%04x->0x%x  ",a,MEM_PAT_N);
        printf("\n");

        read = read_f(a);
        printf("?%04x=0x%x ",a,MEM_PAT_N);
        printf("%s",read == MEM_PAT_N ? " " : "x");

        k=bit_count;
        while(k>-2) {
            if (k !=j) {
                a = 1<<k;
                read = read_f(a);
                printf("?%04x=0x%x ",a,MEM_PAT);
                printf("%s",read == MEM_PAT ? " " : "x");
            }
            if ((k %4) == 0) { printf("\n");}
            k--;
        }
printf("\n");
printf("\n");
        j--;
    }
}


void mem_bitwalk(void* addr,uint16_t count) {

}

