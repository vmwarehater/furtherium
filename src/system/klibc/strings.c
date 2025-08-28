#include "strings.h"
#include <stdint.h>



char* strcpy_s(char* src, char* dest, size_t size){
    int i = 0;
    while(*src != '\0' && i <= size - 2){
        dest[i] = *src;
        i++;
        src++;
    }
    dest[i] = '\0';
    return dest;
}


char* strcpy(char* src, char* dest){
    int i = 0;
    while(*src != '\0'){
        dest[i] = *src;
        i++;
        src++;
    }
    dest[i] = '\0';
    return dest;
}


int strcmp(const char* str1, const char* str2){
    while(1){
        if(*str1 == '\0' && *str2 != '\0'){
            return -1;
        } else if(*str2 == '\0' && *str1 != '\0'){
            return 1;
        } else if(*str1 == '\0' && *str2 == '\0') return 0;
        if(*str2 != *str1){
            if(*str2 >= *str1) return -1;
            else return 1;
        }
        str2++, str1++;
    }
    return 0;
}


int strsplit(char* str, char delimeter, char* res1, 
            size_t res1_size, char* res2, size_t res2_size)
{
    uint8_t change = 0;
    uint64_t res1c = 0;
    uint64_t res2c = 0;
    while(*str != '\0'){
        if(change == 0){
            if(res1c >= res1_size - 2 || *str == delimeter){
                res1[res1c] = '\0';
                change = 1;
                str++;
                continue;
                
            }
            res1[res1c] = *str;
            res1c++;
            str++;
        }
        else {
            if(res2c >= res2_size - 3){
                res2[res2c] = '\0';
                change = 1;
                return 1;
            }
            res2[res2c] = *str;
            res2c++;
            res2[res2c] = '\0';
            str++;
        }
    }
    return 0;
}


void* memcpy(void* dest, const void* src, size_t size){
    volatile uint8_t* pdest = (volatile uint8_t*)dest;
    const volatile uint8_t* psrc = (const volatile uint8_t*)src;

    for (size_t i = 0; i < size; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}


void __stack_chk_fail(){}