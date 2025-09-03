#include "puts.h"
#include "../uri/uri.h"
#include "strings.h"





void putchar(char c){
    send_to_url("device:uart\\write\\char", &c, strlen("\n") + 1);
}

void puts_no_newline(char* string){
    while(*string != '\0'){
        putchar(*string);
        string++;
    }
}

void puts(char* string){
    puts_no_newline(string);
    putchar('\n');
}

char getchar(){
    return (char)((uint64_t)recv_from_url("device:uart\\read\\blocking", 1));
}

char getchar_unblocking(){
    return (char)((uint64_t)recv_from_url("device:uart\\read\\unblocking", 1));
}

// klibc but i make my own functions that don't exist anywhere else :screaming:
// yes this file will be a bunch of puts clones for different stuff with a bunch of buffers
void xputs(uint64_t hexadecimal){
    char s[512];
    xtoa((uint64_t)hexadecimal, s, 30);
    puts_no_newline("0x");
    puts(s);
}

