#include "../board/virt/rtc.h"






void delay_execution(uint64_t seconds){
    int target_sec = get_value_from_rtc() + seconds;
    while(!(get_value_from_rtc() >= target_sec)){
        continue;
    }
}