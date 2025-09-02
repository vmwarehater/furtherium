#include "../coreinit.h"





uint64_t memaddr = 0;
extern uint64_t __end;

void setup_core_system(){
    memaddr = __end;
    return;
}