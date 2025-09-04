#include "kshell.h"
#include "../klibc/puts.h"
#include "../klibc/strings.h"
#include "../../arch/dumpreg.h"
#include "../uri/uri.h"
#include <stdint.h>


static char* commands[] = {
    "echo", "dumpreg", "help",
    "wmem", "rmem", "rurl", "wurl",
    "hostlist"
};

static inline uint8_t write_to_memory_dbg_command(char* arguments){
    if(arguments == NULL || strcmp(arguments, "") == 0){
        puts("please add arguments");
        return 1;
    }
    char memloc[126]; 
    char value[126];
    strsplit(arguments, ' ', memloc, 126, value, 126);
    if(strcmp(memloc, "") == 0 || strcmp(value, "") == 0){
        puts("invalid arguments");
        return 1;
    }
    uint64_t mloc = atox_u64(memloc);
    uint64_t val = atox_u64(value);
    *(volatile uint64_t*)mloc = val;
    puts_no_newline("Wrote Successfully to ");
    xputs(mloc);
    return 0;
}

static inline uint8_t read_from_memory_dbg_command(char* arguments){
    if(arguments == NULL || strcmp(arguments, "") == 0){
        puts("please add arguments");
        return 1;
    }
    uint64_t memloc = atox_u64(arguments);
    puts_no_newline("Value of ");
    xputs_no_newline(memloc);
    puts_no_newline(" is ");
    xputs(*(volatile uint64_t*)memloc);
    return 0;
}

static inline uint8_t read_from_url(char* arguments){
    if(arguments == NULL || strcmp(arguments, "") == 0){
        puts("please add arguments");
        return 1;
    }
    void* res = recv_from_url(arguments, 512);
    puts((char*)res);
    return 0;
}

static inline uint8_t write_to_url(char* arguments){
    if(arguments == NULL || strcmp(arguments, "") == 0){
        puts("please add arguments");
        return 1;
    }
    char url[126]; 
    char value[126];
    strsplit(arguments, ' ', url, 126, value, 126);
    if(strcmp(url, "") == 0 || strcmp(value, "") == 0){
        puts("invalid arguments");
        return 1;
    }
    send_to_url(url, (void*)value, 512);
    return 0;
}

static inline uint8_t list_hosts(char* arguments){
    if(arguments == NULL || strcmp(arguments, "") == 0){
        puts("please add arguments");
        return 1;
    }
    int amount;
    host_t* h = return_hosts_from_scheme(arguments, &amount);
    if(h == NULL){
        puts("couldn't find any hosts");
    }
    puts("\n----------------------------------------");
    for(int i = 0; i < amount; i++){
        puts(h[i].name);
    }
    puts("----------------------------------------\n");
    return 0;
}

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
                case 3: {
                    uint8_t res = write_to_memory_dbg_command(arguments);
                    if(res == 1) puts("wmem failed");
                    break;
                }
                case 4: {
                    uint8_t res = read_from_memory_dbg_command(arguments);
                    if(res == 1) puts("rmem failed");
                    break;
                }
                case 5: {
                    uint8_t res = read_from_url(arguments);
                    if(res == 1) puts("rurl failed");
                    break;
                }
                case 6: {
                    uint8_t res = write_to_url(arguments);
                    if(res == 1) puts("wurl failed");
                    break;
                }
                case 7: {
                    uint8_t res = list_hosts(arguments);
                    if(res == 1) puts("hostlist failed");
                    break;
                }
                default:
                    puts("Unimplemented");
                    break; 
            }
            return;
        }
    }
    puts("unknown command");
}




void begin_backup_kernel_shell(){
    puts("\n");
    while(1){
        puts_no_newline("dbg> ");
        char buffer[512];
        char command[255];
        char argument[255];
        gets_s(buffer, 512, 1);
        strsplit(buffer, ' ', command, 255, argument, 255);
        match_to_command(command, argument);
    }
}