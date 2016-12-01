#include "memtest8.h"
#include "memtest8.h"
#include <stdio.h>

void mem_bitwalk_test( void(*write_f)(uint16_t, uint8_t),
                      uint8_t(*read_f)(uint16_t),
                      uint16_t addr,uint16_t count) {
uint8_t read;
uint8_t bit;
uint8_t i;

    //Test data bus, all 8 bits
    bit=1;
    while(count) {
        for(i=0;i<8;i++) {
            write_f(addr,bit);
            read = read_f(addr);
            printf("%04x?%s ",addr,read == bit ? " " : "!");
        }
        printf("\n");
        addr++;
        count--;
    }
}

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

    //Iterate through each address line
    while(j>-2) {
        //Write same thing to each line
        i=bit_count;
        while(i>-2) {
            a = 1<<i;
            write_f(a,MEM_PAT);
            printf("%04x->0x%x  ",a, MEM_PAT);
            if ((i % 0x4) == 0) { printf("\n");}
            i--;
        }

        //Write the opposite to 1 line
        a = 1<<j;
        write_f(a,MEM_PAT_N);
        printf("%04x->0x%x  ",a,MEM_PAT_N);
        printf("\n");

        //Did the line retain the new value?
        read = read_f(a);
        printf("?%04x=0x%x ",a,MEM_PAT_N);
        printf("%s",read == MEM_PAT_N ? " " : "x");

        //Test all the other lines now to make
        // sure they weren't changed
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

