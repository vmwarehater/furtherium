
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

    // mov r0, 0 (sets kcall so it prints the value in r1)
    uint64_t ins1[3];
    ins1[0] = 0x2;
    ins1[1] = 0x0;
    ins1[2] = 0x0;
    interpret_vm_bytecode_line(ins1);

    // mov r2, 3
    ins1[0] = 0x2;
    ins1[1] = 0x2;
    ins1[2] = 0x3;
    interpret_vm_bytecode_line(ins1);

    // mov r3, 3
    ins1[0] = 0x2;
    ins1[1] = 0x3;
    ins1[2] = 0x2;
    interpret_vm_bytecode_line(ins1);

    // add r1, r2, r3
    uint64_t ins2[4];
    ins2[0] = 0x8;
    ins2[1] = 0x1;
    ins2[2] = 0x2;
    ins2[3] = 0x3;
    interpret_vm_bytecode_line(ins2);

    // kcall (prints value in r1)
    uint64_t ins3[1];
    ins3[0] = 0x6;
    interpret_vm_bytecode_line(ins3);
    
    
    puts("\n\nKernel finished and no init found, starting kernel debugger.....");
    // system ends, start emergency shell on the UART
    begin_backup_kernel_shell();
}