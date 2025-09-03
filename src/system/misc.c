#include "uri/uri.h"











void delay_execution(uint64_t seconds){
    int target_sec = (uint64_t)recv_from_url("device:rtc", 1) + seconds;
    while(!((uint64_t)recv_from_url("device:rtc", 1) >= target_sec)){
        continue;
    }
}