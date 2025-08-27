#include "../rtc.h"
#include <stdint.h>



#define RTC_ADDRESS 0x09010000



uint64_t get_value_from_rtc(){
    return *(volatile uint64_t*)RTC_ADDRESS;
}


