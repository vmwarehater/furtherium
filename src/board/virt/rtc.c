#include "rtc.h"
#include <stdint.h>






uint64_t get_value_from_rtc(){
    return *(volatile uint64_t*)RTC_ADDRESS;
}


