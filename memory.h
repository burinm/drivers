#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include "mylib.h"
extern uint8_t mylib_errno;

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length);
int8_t my_memzero(uint8_t *src, uint32_t length);
int8_t my_reverse(uint8_t * src, uint32_t length);
int32_t my_strlen(uint8_t * src);

#endif
