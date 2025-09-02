#include "puts.h"
#include "../../board/uart.h"
#include "strings.h"






void puts(char* string){
    write_string_to_uart(string);
}

// klibc but i make my own functions that don't exist anywhere else :screaming:
// yes this file will be a bunch of puts clones
void xputs(uint64_t hexadecimal){
    char s[512];
    xtoa((uint64_t)hexadecimal, s, 30);
    puts("0x");
    puts(s);
    puts("\n");
}

