#include "../coreinit.h"




uint64_t MMIO_BASE = 0;



void setup_core_system(){
    MMIO_BASE = 0xFE000000;
    return;
}