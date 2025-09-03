#include "uartdev.h"
#include "../uri/uri.h"
#include "../../board/uart.h"
#include "../klibc/strings.h"
#include <stddef.h>








static inline void send_handler(void* data, size_t size, char* path){
    if(strcmp("write\\char", path) == 0){
        char* ch = (char*)data;
        char c = ch[0];
        write_to_uart(c);
    }
}

static inline void* recv_handler(size_t size, char* path){
    if(strcmp("read\\blocking", path) == 0){
        return (void*)((uint64_t)read_from_uart());
    } else if(strcmp("read\\unblocking", path)){
        return (void*)((uint64_t)read_from_uart_without_blocking());
    }
    return NULL;
}


void setup_uart_device(){
    setup_uart();

    host_t host = {
        "uart",
        send_handler,
        recv_handler
    };
    create_host("device", host);
}