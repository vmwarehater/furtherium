
#include <stddef.h>
#include <stdint.h>
#include "arch/exception.h"
#include "board/coreinit.h"
#include "board/rtc.h"
#include "board/uart.h"
#include "system/mem/chunkalloc.h"
#include "system/misc.h"
#include "system/klibc/strings.h"
#include "system/klibc/strings.h"

#include "system/uri/uri.h"

extern uint64_t sp_top;



void kernel_entry(void){
    setup_uart();
    setup_core_system();
    chunk_allocator_setup();    
    write_string_to_uart("Loading Furtherium.....\n\n");
    load_exception_vector();
    create_scheme("device");
    
    char idk[30];
    char* h = allocate_single_chunk();

    xtoa((uint64_t)h, idk, 30);
    write_string_to_uart(idk);
    write_string_to_uart("\n");

    // this goes backwards and then forwards again??
    // idk, needs to be fixed
    char* l = allocate_single_chunk();
    char* pp = allocate_single_chunk();

    xtoa((uint64_t)pp, idk, 30);
    write_string_to_uart(idk);
    write_string_to_uart("\n");

    free_single_chunk(h);
    char* p = allocate_single_chunk();

    xtoa((uint64_t)h, idk, 30);
    write_string_to_uart(idk);
    write_string_to_uart("\n");



    while(1){
        write_to_uart(get_value_from_rtc());
        delay_execution(1);
    }
}