#include "../coreinit.h"




uint64_t MMIO_BASE = 0;

uint64_t memaddr = 0;
extern uint64_t __end;

void setup_core_system(){
    MMIO_BASE = 0xFE000000;
    memaddr = __end;
    return;
}