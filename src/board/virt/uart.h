#ifndef UART_H_ICNLUDED
#define UART_H_ICNLUDED








#include <stdint.h>

#define UART_ADDRESS 0x09000000

void write_to_uart(uint8_t c);
uint8_t read_from_uart_without_blocking();
void write_string_to_uart(char* string);







#endif