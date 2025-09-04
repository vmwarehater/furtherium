
#include <stddef.h>
#include <stdint.h>
#include "arch/exception.h"
#include "board/coreinit.h"
#include "system/coredevices/coredev.h"
#include "system/klibc/puts.h"

#include "system/kshell/kshell.h"
#include "system/mem/chunkalloc.h"

#include "system/uri/uri.h"

extern uint64_t sp_top;



void kernel_entry(void){
    setup_core_system();
    create_scheme("device");
    setup_core_devices();
    load_exception_vector();
    chunk_allocator_setup();  
    puts("Loaded Core Utilites.....\n\n");

    char* h = allocate_single_chunk();

    xputs((uint64_t)h);
    
    char* l = allocate_single_chunk();
    xputs((uint64_t)l);
    char* pp = allocate_multiple_chunks(10);
    char* ll = allocate_multiple_chunks(10);
    xputs((uint64_t)pp);
    xputs((uint64_t)ll);
    free_multiple_chunks(pp, 10);
    char* p = allocate_multiple_chunks(4);
    xputs((uint64_t)p);
    
    puts("\n\nKernel finished and no init found, starting kernel debugger.....");
    // system ends, start emergency shell on the UART
    begin_backup_kernel_shell();
}