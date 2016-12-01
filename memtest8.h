#ifndef __MEMTEST_H__
#define __MEMTEST_H__

#include <stdint.h>

/* Memory test routines for RAM

    These tests are for 8bit data
    and a 16bit address bus max

*/

#define MEM_TEST8_HIGHEST_BIT   0x80
#define MEM_TEST8_ADDR_BITS     16

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

/* Walking 1s bit test */
void mem_bitwalk(void* addr,uint16_t count);

#endif
