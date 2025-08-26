
#include <stdint.h>
#include "arch/aarch64/exception.h"
#include "board/virt/rtc.h"
#include "board/virt/uart.h"
#include "system/misc.h"





void kernel_entry(){
    write_string_to_uart("Loading Futherium.....\n\n");
    load_exception_vector();
    while(1){
        write_to_uart(get_value_from_rtc());
        delay_execution(1);
    }
}