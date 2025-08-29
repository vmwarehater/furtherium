#include "chunkalloc.h"
#include <stdint.h>

extern uint64_t memaddr;

static uint64_t curMem = 0;



void chunk_allocator_setup(){
    curMem = memaddr;
    *(volatile uint64_t*)curMem = 0;
}


void* allocate_single_chunk(){
    for(uint64_t i = memaddr; i < curMem; i+=0x1000){
        if(*(volatile uint64_t*)i == 0){
            *(volatile uint64_t*)i = 1;
            uint64_t res = i + 8;
            return (void*)res;
        }
    }
    curMem += 0x1000;
    *(volatile uint64_t*)curMem = 1;
    uint64_t res = curMem + 8;
    return (void*)res;
}

void free_single_chunk(void* address){
    *(volatile uint64_t*)(address - 8) = 0; 
}