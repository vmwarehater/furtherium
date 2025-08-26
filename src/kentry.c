
#include <stdint.h>
#include "arch/aarch64/exception.h"
#include "board/virt/rtc.h"
#include "board/virt/uart.h"
#include "system/misc.h"





void kernel_entry(){
    load_exception_vector();
    write_string_to_uart("Futherium Educational Kernel\n\n");
    while(1){
        write_to_uart(get_value_from_rtc());
        delay_execution(1);
    }
}