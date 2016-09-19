#ifndef __REVERSE_H__
#define __REVERSE_H__

#include <stdint.h>

uint8_t reverse(uint8_t *str, int length);
/*
 * Reverse a string up to length
 * Warning, currently doesn't check
 * for length > strlen(str)
 *
 * IN - str, pointer to NULL terminated string 
 * 	length, length of string not including NULL
 * 
 * OUT - 0, o.k, -1 error
 *       0 - str pointer will contain reversed string
 *   error - str pointer will contain original string
 */

#endif
