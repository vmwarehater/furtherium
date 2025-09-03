#include "../exception.h"
#include "../dumpreg.h"
#include "../../system/klibc/puts.h"
#include "../../system/kshell/kshell.h"


void exception_unimplemented(){
    puts("!! Unknown exception has occured, halting system !!");
    while(1){continue;}
}

void exception_error(){
    puts("\n\n\n!!! An error has occured, dumping registers !!!\n\n\n");
    dump_and_print_registers();
    puts("\n\n\n!!! Starting Emergency Shell !!!\n\n\n");
    begin_backup_kernel_shell();
    //puts("\n!!! Halting System !!!\n");
    while(1){continue;}
}