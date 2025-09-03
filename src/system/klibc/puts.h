#ifndef PUTS_H_INCLUDED
#define PUTS_H_INCLUDED













#include <stdint.h>






void putchar(char c);
void puts_no_newline(char* string);
void puts(char* string);
char getchar();
char getchar_unblocking();
void gets_s(char* string, uint16_t size, uint8_t cleanBuffer);
void xputs(uint64_t hexadecimal);














#endif