#include "chunkalloc.h"
#include <stdint.h>

extern uint64_t memaddr;

static uint64_t curMem = 0;



void chunk_allocator_setup(){
    curMem = memaddr;
    *(volatile uint64_t*)curMem = 0;
}

void* allocate_single_chunk(){
    for(uint64_t i = memaddr; i < curMem; i+=0x400){
        if(*(volatile uint64_t*)i == 0){
            *(volatile uint64_t*)i = 1;
            uint64_t res = i + 8;
            return (void*)res;
        }
    }
    curMem += 0x400;
    *(volatile uint64_t*)curMem = 1;
    uint64_t res = curMem + 8;
    return (void*)res;
}

void free_single_chunk(void* address){
    *(volatile uint64_t*)(address - 8) = 0; 
}

void* allocate_multiple_chunks(uint64_t amount){
    for(uint64_t i = memaddr; i < curMem; i+=0x400){
        if(*(volatile uint64_t*)i == 0){
            uint64_t valid = 1;
            for(uint64_t j = i; j < i + amount * 0x400; j+=0x400){
                if(*(volatile uint64_t*)j != 0){
                    valid = 0;
                    break;
                }
            }
            if(valid != 1) continue;
            for(uint64_t j = i; j < i + amount * 0x400; j+=0x400){
                *(volatile uint64_t*)j = 1;
            }
            return (void*)i + 8;
        }
    }
    uint64_t return_value = curMem += 0x400;
    for (uint64_t j = 0; j < amount; j++) {
        *(volatile uint64_t*)curMem = 1;
        curMem += 0x400;
    }
    return (void*)return_value + 8;
}

void free_multiple_chunks(void* address, uint64_t amount){
    for(uint64_t i = (uint64_t)address; i < (uint64_t)address + amount * 0x400; i+=0x400){
        *(volatile uint64_t*)(i - 8) = 0; 
    }
}