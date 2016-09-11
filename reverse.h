#ifndef DEFINE_H
#define DEFINE_H
/*
 * Reverse a string up to length
 * Warning, currently doesn't check
 * for length > strlen(str)
 *
 * IN - str, pointer to NULL terminated string 
 * 	length, length of string not including NULL
 * 
 * OUT - 0, o.k, -1 error
 *       str pointer will contain reversed string.
 */

char reverse(char *str, int length);
#endif
