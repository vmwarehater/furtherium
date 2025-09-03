
#include <stddef.h>
#include <stdint.h>
#include "arch/dumpreg.h"
#include "arch/exception.h"
#include "board/coreinit.h"
#include "board/rtc.h"
#include "board/uart.h"
#include "system/klibc/puts.h"
#include "system/mem/chunkalloc.h"
#include "system/misc.h"

#include "system/uri/uri.h"

extern uint64_t sp_top;



void kernel_entry(void){
    setup_core_system();
    setup_uart();
    load_exception_vector();
    chunk_allocator_setup();  

    puts("Loading Furtherium.....\n\n");

    create_scheme("device");
    
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
    
    while(1){
        write_to_uart(get_value_from_rtc());
        delay_execution(1);
    }
}