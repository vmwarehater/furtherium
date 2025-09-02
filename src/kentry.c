
#include <stddef.h>
#include <stdint.h>
#include "arch/exception.h"
#include "board/coreinit.h"
#include "board/rtc.h"
#include "board/uart.h"
#include "system/klibc/puts.h"
#include "system/mem/chunkalloc.h"
#include "system/misc.h"
#include "system/klibc/strings.h"
#include "system/klibc/strings.h"

#include "system/uri/uri.h"

extern uint64_t sp_top;



void kernel_entry(void){
    setup_core_system();
    setup_uart();
    chunk_allocator_setup();    
    puts("Loading Furtherium.....\n\n");
    load_exception_vector();
    create_scheme("device");
    
    char* h = allocate_single_chunk();

    xputs((uint64_t)h);
    
    // this goes backwards and then forwards again??
    // idk, needs to be fixed
    char* l = allocate_single_chunk();
    xputs((uint64_t)l);
    char* pp = allocate_single_chunk();
    xputs((uint64_t)pp);
    
    free_single_chunk(h);
    char* p = allocate_single_chunk();
    xputs((uint64_t)p);
    

    while(1){
        write_to_uart(get_value_from_rtc());
        delay_execution(1);
    }
}