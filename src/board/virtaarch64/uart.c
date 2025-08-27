#include "../uart.h"
#include <stdint.h>

#define UART_ADDRESS 0x09000000


void write_to_uart(uint8_t c){
    *(volatile uint8_t*)UART_ADDRESS = c;
}

uint8_t read_from_uart_without_blocking(){
    return *(volatile uint8_t*)UART_ADDRESS;
}

void write_string_to_uart(char* string){
    while(*string != '\0'){
        write_to_uart(*string);
        string++;
    }
}