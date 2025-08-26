#include "exception.h"






void exception_unimplemented(){
    *(volatile uint64_t*)0x09000000 = '?';
    while(1){continue;}
}

void exception_error(){
    *(volatile uint64_t*)0x09000000 = 'e';
    while(1){continue;}
}