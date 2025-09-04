#include "puts.h"
#include "../uri/uri.h"
#include "strings.h"





void putchar(char c){
    send_to_url("device:uart\\write\\char", &c, sizeof(char));
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

// taken from the nearerOS impl, my other OS which this kernel will be replacing that kernel for
void gets_s(char* string, uint16_t size, uint8_t cleanBuffer){
    if(cleanBuffer == 1){
        for(int i = 0; i <= size; i++){
            string[i] = '\0';
        }
    }
    uint16_t curIndex = 0;
    uint16_t sizeCutByTwo = size - 2;
    while(curIndex < sizeCutByTwo){
        char character = getchar();
        if(character == 13) break;
        // if(character == 127){
        //     string[curIndex] = '\0';
        //     curIndex--;
        //     string[curIndex] = '\0';
        //     brdWriteCharacterIntoUart('\b');
        // }
        putchar(character);
        string[curIndex] = character;
        curIndex++;
    }
    string[curIndex] = '\0';
    putchar('\n');
}

// klibc but i make my own functions that don't exist anywhere else :screaming:
// yes this file will be a bunch of puts clones for different stuff with a bunch of buffers
void xputs(uint64_t hexadecimal){
    char s[512];
    xtoa((uint64_t)hexadecimal, s, 30);
    puts_no_newline("0x");
    puts(s);
}


void xputs_no_newline(uint64_t hexadecimal){
    char s[512];
    xtoa((uint64_t)hexadecimal, s, 30);
    puts_no_newline("0x");
    puts_no_newline(s);
}
