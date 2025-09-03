#include "../exception.h"
#include "../../board/uart.h"
#include "../dumpreg.h"




void exception_unimplemented(){
    write_string_to_uart("!! Unknown Exception has Occured, halting system !!");
    while(1){continue;}
}

void exception_error(){
    write_string_to_uart("!!! An error has occured, dumping registers !!!\n\n\n");
    dump_and_print_registers();
    write_string_to_uart("\n!!! Halting System !!!\n");
    while(1){continue;}
}