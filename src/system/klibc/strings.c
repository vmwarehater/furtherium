#include "strings.h"
#include "maths.h"
#include <stddef.h>
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

size_t strlen(const char* string){
    size_t i = 0;
    while(*string != '\0'){
        string++;
        i++;
    }
    return i;
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

static inline char hex_to_char(uint64_t hex){
    if(hex >= 0x0 && hex <= 0x9){
        return 48 + hex;
    } else return (65 - 10) + hex;
}


uint8_t xtoa(uint64_t integer, char* string, uint16_t size){
    for(int i = 0; i <= size; i++){
        string[i] = 0x0;
    }
    if(integer == 0){
        if(size <= 2){
            return 1;
        }
        string[0] = '0';
        string[1] = '\0';
        return 0;
    }
    uint64_t temp = integer;
    uint16_t digits = 0;
    while(temp > 0x0){
        temp /= 16;
        digits++;
    }
    temp = integer;
    uint64_t index = 0;
    for(int i = digits - 1; i >= 0; i--){
        if(index >= size - 1){
            break;
        }
        uint64_t div = pow_64(16, i);
        uint64_t singleDigit = temp / div;
        string[index] = hex_to_char(singleDigit);
        index++;
        temp %= div;
    }
    string[index] = '\0';
    return 0;
} 



uint64_t atoi_u64(const char* string){
    uint64_t result = 0;

    while(*string != '\0'){
        if(*string >= 48 && *string <= 57){
            result *= 10;
            result += (*string - 48);
        }
        string++;
    }
    return result;
}

int atoi(const char* string){
    int result = 0;

    while(*string != '\0'){
        if(*string >= 48 && *string <= 57){
            result *= 10;
            result += (*string - 48);
        }
        string++;
    }
    return result;
}


uint64_t atox_u64(const char* string){
    uint64_t result = 0;

    while(*string != '\0'){
        if(*string >= 48 && *string <= 57 || *string >= 65 && *string <= 70){
            result *= 16;
            result += (*string - 48);
        }
        string++;
    }
    return result;
}