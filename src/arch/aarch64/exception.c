#include "../exception.h"
#include "../../board/uart.h"





void exception_unimplemented(){
    write_string_to_uart("Unknown Exception has Occured, halting system");
    while(1){continue;}
}

void exception_error(){
    write_string_to_uart("An error has occured, dumping registers...\n\n\n");
    // TODO: dump registers
    while(1){continue;}
}