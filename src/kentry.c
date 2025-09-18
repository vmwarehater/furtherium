
#include <stddef.h>
#include <stdint.h>
#include "arch/exception.h"
#include "board/coreinit.h"
#include "system/coredevices/coredev.h"
#include "system/klibc/puts.h"

#include "system/kshell/kshell.h"
#include "system/mem/chunkalloc.h"

#include "system/nearvm/nearvm.h"
#include "system/uri/uri.h"

extern uint64_t sp_top;



void kernel_entry(void){
    setup_core_system();
    chunk_allocator_setup();  

    create_scheme("device");
    create_scheme("proc");
    setup_core_devices();
    load_exception_vector();
    puts("Loaded Core Utilites.....\n\n");

    
    uint64_t ins[50];
    int i = 0;

    // funcaskip 0x1 4 (sets func there and skips the next 3 instructions)
    ins[i++] = 0xD;
    ins[i++] = 0x1;
    ins[i++] = 4;

    // mov r0, 0
    ins[i++] = 0x2;
    ins[i++] = 0x0;
    ins[i++] = 0x0;

    // mov r1, 1
    ins[i++] = 0x2;
    ins[i++] = 0x1;
    ins[i++] = 1;   

    // kcall
    ins[i++] = 0x6;

    // ret
    ins[i++] = 0xE;

    // funcaskip 0x2 4 (sets func there and skips the next 3 instructions)
    ins[i++] = 0xD;
    ins[i++] = 0x2;
    ins[i++] = 4;

    // mov r0, 0
    ins[i++] = 0x2;
    ins[i++] = 0x0;
    ins[i++] = 0x0;

    // mov r1, 2
    ins[i++] = 0x2;
    ins[i++] = 0x1;
    ins[i++] = 2;   

    // kcall
    ins[i++] = 0x6;

    // ret
    ins[i++] = 0xE;


    // mov r3, 2
    ins[i++] = 0x2;
    ins[i++] = 0x3;
    ins[i++] = 5;

    // mov r4, 2
    ins[i++] = 0x2;
    ins[i++] = 0x4;
    ins[i++] = 4;

    // cmpe r3, r4, 0x2 (jumps to func 0x2 if r3 and r4 is equal)
    ins[i++] = 0xA;
    ins[i++] = 0x3;
    ins[i++] = 0x4;
    ins[i++] = 0x2;


    // cmpg r3, r4, 0x1 (jumps to func 0x1 if r3 is greater then r4)
    ins[i++] = 0xC;
    ins[i++] = 0x3;
    ins[i++] = 0x4;
    ins[i++] = 0x1;
    

    interpret_vm_bytecode(ins);
    
    puts("\n\nKernel finished and no init found, starting kernel debugger.....");
    // system ends, start emergency shell on the UART
    begin_backup_kernel_shell();
}