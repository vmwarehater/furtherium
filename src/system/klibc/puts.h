#ifndef PUTS_H_INCLUDED
#define PUTS_H_INCLUDED













#include <stdint.h>







void puts(char* string);
void putchar(char c);
char getchar();
char getchar_unblocking();
void puts_no_newline(char* string);
void xputs(uint64_t hexadecimal);














#endif