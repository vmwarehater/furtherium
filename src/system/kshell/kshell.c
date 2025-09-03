#include "kshell.h"
#include "../klibc/puts.h"
#include "../klibc/strings.h"
#include "../../arch/dumpreg.h"
#include <stdint.h>


static char* commands[] = {
    "echo", "dumpreg", "help"
};





static inline void match_to_command(char* command, char* arguments){
    int amount = sizeof(commands) / sizeof(commands[0]);
    for(int i = 0; i < amount; i++){
        if(strcmp(commands[i], command) == 0){
            switch(i){
                case 0:
                    puts(arguments);
                    break;
                case 1:
                    dump_and_print_registers();
                    break;
                case 2:
                    puts("-----------------------------------");
                    for(int i = 0; i < amount; i++){
                        puts(commands[i]);
                    }
                    puts("-----------------------------------");
                    break;
                default:
                    break; 
            }
            return;
        }
    }
    puts("unknown command");
}




void begin_backup_kernel_shell(){
    puts("\n\n");
    while(1){
        puts_no_newline("dbg> ");
        char buffer[512];
        char command[288];
        char argument[288];
        gets_s(buffer, 512, 1);
        strsplit(buffer, ' ', command, 288, argument, 288);
        match_to_command(command, argument);
    }
}