#ifndef __MEMTEST_H__
#define __MEMTEST_H__

#include <stdint.h>

#define MEM_PAT     (0xaa)
#define MEM_PAT_N   (0x55)


/* Memory test routines for RAM

    These tests are for 8bit data
    and a 16bit address bus max

*/

#define MEM_TEST8_HIGHEST_BIT   0x80
#define MEM_TEST8_ADDR_BITS     16

/* Walking 1s bit test

    Test data bus by writing/reading each bit

   input:
        write function
        read function
        Address to use for test
        Count up how many additional addresses 

*/
void mem_bitwalk_test(void(*write_f)(uint16_t, uint8_t),
                 uint8_t(*read_f)(uint16_t),
                 uint16_t addr,uint16_t count);

/* mem_addr_test - test address lines

  Writes to every address line, and then writes
   to each of the lines to make sure memory accesses
   only affect a single address

   input:
        write function
        read function
        Highest writable address +1
*/
uint8_t mem_addr_test(void(*write_f)(uint16_t, uint8_t),
                     uint8_t(*read_f)(uint16_t),
                     uint32_t addr);


#endif
