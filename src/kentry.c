
#include <stddef.h>
#include <stdint.h>
#include "arch/exception.h"
#include "board/coreinit.h"
#include "board/rtc.h"
#include "board/uart.h"
#include "system/misc.h"
#include "system/klibc/strings.h"
#include "system/uri/uri.h"




void SendHandler(void* data, size_t size, char* path){
    write_string_to_uart(data);
    write_string_to_uart(path);
}

void* RecvHandler(size_t size, char* path){
    *(volatile uint8_t*)0x40001000 = path[0];
    return (void*)0x40001000;
}

void kernel_entry(void){
    setup_core_system();
    setup_uart();
    write_string_to_uart("Loading Futherium.....\n\n");
    load_exception_vector();
    create_scheme("device");
    host_t host = {
        "test",
        SendHandler,
        RecvHandler
    };
    create_host("device", host);
    send_to_url("device:test\\paths\\pol", "Hello!", 64);
    
    while(1){
        write_to_uart(get_value_from_rtc());
        delay_execution(1);
    }
}