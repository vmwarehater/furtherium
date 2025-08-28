#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED











#include <stdint.h>
#include <stddef.h>



char* strcpy_s(char* src, char* dest, size_t size);
char* strcpy(char* src, char* dest);
int strcmp(const char* str1, const char* str2);
int strsplit(char* str, char delimeter, char* res1, 
            size_t res1_size, char* res2, size_t res2_size);
void* memcpy(void* dest, const void* src, size_t size);


#endif