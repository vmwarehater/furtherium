#include "../uart.h"
#include <stdint.h>





void setup_uart(){
    // STUB
    return;
}

void write_to_uart(uint8_t c){
    // STUB
    return;
}

uint8_t read_from_uart_without_blocking(){
    // STUB
    return 0;
}
uint8_t read_from_uart(){
    // STUB
    return 0;
}
void write_string_to_uart(char* string){
    while(*string != '\0'){
        write_to_uart(*string);
        string++;
    }
}