#include "../uri/uri.h"
#include "../../board/rtc.h"
#include <stddef.h>








static inline void send_handler(void* data, size_t size, char* path){
    // STUB
    return;
}

static inline void* recv_handler(size_t size, char* path){
    return (void*)get_value_from_rtc();
}


void setup_rtc_device(){
    host_t host = {
        "rtc",
        send_handler,
        recv_handler
    };
    create_host("device", host);
}