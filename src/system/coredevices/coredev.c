#include "coredev.h"
#include "rtcdev.h"
#include "uartdev.h"
















void setup_core_devices(){
    setup_uart_device();
    setup_rtc_device();
}