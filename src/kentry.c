
#include <stdint.h>
#include "arch/exception.h"
#include "board/coreinit.h"
#include "board/rtc.h"
#include "board/uart.h"
#include "system/misc.h"





void kernel_entry(void){
    setup_core_system();
    setup_uart();
    write_string_to_uart("Loading Futherium.....\n\n");
    load_exception_vector();
    while(1){
        //write_to_uart(get_value_from_rtc());
        //delay_execution(1);
    }
}