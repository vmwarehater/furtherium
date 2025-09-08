
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

    // // mov r0, 0 (sets kcall so it prints the value in r1)
    // uint64_t ins1[3];
    // ins1[0] = 0x2;
    // ins1[1] = 0x0;
    // ins1[2] = 0x0;
    // interpret_vm_bytecode_line(ins1);

    // // mov r2, 3
    // ins1[0] = 0x2;
    // ins1[1] = 0x2;
    // ins1[2] = 0x3;
    // interpret_vm_bytecode_line(ins1);

    // // mov r3, 3
    // ins1[0] = 0x2;
    // ins1[1] = 0x3;
    // ins1[2] = 0x2;
    // interpret_vm_bytecode_line(ins1);

    // // add r1, r2, r3
    // uint64_t ins2[4];
    // ins2[0] = 0x8;
    // ins2[1] = 0x1;
    // ins2[2] = 0x2;
    // ins2[3] = 0x3;
    // interpret_vm_bytecode_line(ins2);

    // // kcall (prints value in r1)
    // uint64_t ins3[1];
    // ins3[0] = 0x6;
    // interpret_vm_bytecode_line(ins3);
    
    uint64_t ins[20];
    // mov r0, 0 (kcall checks for r0, 0 means print whatever is in r1)
    ins[0] = 0x2;
    ins[1] = 0x0;
    ins[2] = 0x0;
    // mov r2, 3
    ins[3] = 0x2;
    ins[4] = 0x2;
    ins[5] = 0x3;
    // mov r3, 2
    ins[6] = 0x2;
    ins[7] = 0x3;
    ins[8] = 0x2;
    // sub r1, r2, r3
    ins[9] = 0x8;
    ins[10] = 0x1;
    ins[11] = 0x2;
    ins[12] = 0x3;
    // func 0x1 
    ins[13] = 0x9;
    ins[14] = 0x1;
    // kcall
    ins[15] = 0x6;
    // jmp 0x1
    ins[16] = 0x5;
    ins[17] = 0x1;
    interpret_vm_bytecode(ins);
    
    puts("\n\nKernel finished and no init found, starting kernel debugger.....");
    // system ends, start emergency shell on the UART
    begin_backup_kernel_shell();
}