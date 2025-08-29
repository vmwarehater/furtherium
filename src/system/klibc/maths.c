#include "maths.h"







uint64_t pow_64(uint64_t number, uint64_t power){
    uint64_t result = 1;
    for(int i = 0; i < power; i++){
        result *= number;
    }
    return result;
}