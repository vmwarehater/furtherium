#include "../coreinit.h"






uint64_t memaddr = 0;

void setup_core_system(){
    memaddr = 0x50000 + 0x40100000;
    return;
}