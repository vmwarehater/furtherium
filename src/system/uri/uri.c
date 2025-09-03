#include "uri.h"
#include <stddef.h>
#include "../klibc/strings.h"


#define AMOUNT_OF_SCHEMES 10
#define AMOUNT_OF_HOSTS_PER_SCHEME 20

typedef struct _scheme {
    char name[NAMING_SIZE];
    host_t hosts[AMOUNT_OF_HOSTS_PER_SCHEME];
    uint64_t curHost;
} scheme_t;


scheme_t schemes[AMOUNT_OF_SCHEMES];
uint64_t curScheme = 0;

uint8_t create_scheme(char* scheme_name){
    if(curScheme >= AMOUNT_OF_SCHEMES - 2){
        return 1;
    }
    strcpy_s(scheme_name, schemes[curScheme].name, NAMING_SIZE);
    schemes[curScheme].curHost = 0;
    curScheme++;
    return 0;
}


uint8_t create_host(char* scheme_name, host_t host){
    for(int i = 0; i <= curScheme; i++){
        if(strcmp(scheme_name, schemes[i].name) == 0){
            if(schemes[i].curHost >= AMOUNT_OF_HOSTS_PER_SCHEME - 1){
                return 1;
            }
            strcpy_s(host.name, schemes[i].hosts[schemes[i].curHost].name, NAMING_SIZE);
            schemes[i].hosts[schemes[i].curHost].recv_handler = host.recv_handler;
            schemes[i].hosts[schemes[i].curHost].send_handler = host.send_handler;
            schemes[i].curHost++;
            return 0;
        }
    }
    return 2;
}

uint8_t send_to_url(char* url, void* data, uint64_t size){
    char scheme[NAMING_SIZE];
    char hostandpath[NAMING_SIZE + 1024];
    char host[NAMING_SIZE];
    char path[1024];
    int sch = -1;
    int hos = -1;
    strsplit(url, 
        ':', scheme, 
        NAMING_SIZE, hostandpath, NAMING_SIZE + 1024);
    strsplit(hostandpath, 
        '\\', host, 
        NAMING_SIZE, path,1024);
    for(int i = 0; i <= curScheme; i++){
        if(strcmp(scheme, schemes[i].name) == 0){
            sch = i;
            break;
        }
    }
    if(sch == -1) return 1;
    for(int i = 0; i <= schemes[sch].curHost; i++){
        if(strcmp(host, schemes[sch].hosts[i].name) == 0){
            hos = i;
        }
    }
    if(hos == -1) return 2;
    schemes[sch].hosts[hos].send_handler(data, size, path);
    return 0;
}


void* recv_from_url(char* url, uint64_t size){
    char scheme[NAMING_SIZE];
    char hostandpath[NAMING_SIZE + 1024];
    char host[NAMING_SIZE];
    char path[1024];
    int sch = -1;
    int hos = -1;
    strsplit(url, 
        ':', scheme, 
        NAMING_SIZE, hostandpath, NAMING_SIZE + 1024);
    strsplit(hostandpath, 
        '\\', host, 
        NAMING_SIZE, path,1024);
    for(int i = 0; i <= curScheme; i++){
        if(strcmp(scheme, schemes[i].name) == 0){
            sch = i;
            break;
        }
    }
    if(sch == -1) return NULL;
    for(int i = 0; i <= schemes[sch].curHost; i++){
        if(strcmp(host, schemes[sch].hosts[i].name) == 0){
            hos = i;
        }
    }
    if(hos == -1) return NULL;
    return schemes[sch].hosts[hos].recv_handler(size, path);
}


host_t* return_hosts_from_scheme(char* scheme, int* amount){
    for(int i = 0; i <= curScheme; i++){
        if(strcmp(scheme, schemes[i].name) == 0){
            *amount = schemes[i].curHost;
            return schemes[i].hosts;
        }
    }
    return NULL;
}