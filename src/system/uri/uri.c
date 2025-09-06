#include "uri.h"
#include <stddef.h>
#include "../klibc/strings.h"
#include "../mem/chunkalloc.h"


#define AMOUNT_OF_SCHEMES 10

typedef struct _scheme {
    char name[NAMING_SIZE];
    host_llist_t* list;
    host_llist_t* initial;
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
    schemes[curScheme].list = (host_llist_t*)allocate_single_chunk();
    schemes[curScheme].initial = schemes[curScheme].list;
    schemes[curScheme].initial->isInital = 1;
    curScheme++;
    return 0;
}


uint8_t create_host(char* scheme_name, host_t host){
    for(int i = 0; i <= curScheme; i++){
        if(strcmp(scheme_name, schemes[i].name) == 0){
            schemes[i].list->next = (host_llist_t*)allocate_single_chunk();
            if(schemes[i].list->next == NULL) return 1;
            schemes[i].list->next->isInital = 0;
            schemes[i].list->next->prev = schemes[i].list;
            schemes[i].list = schemes[i].list->next;
            strcpy_s(host.name, schemes[i].list->host.name, NAMING_SIZE);
            schemes[i].list->host.recv_handler = host.recv_handler;
            schemes[i].list->host.send_handler = host.send_handler;
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
    host_llist_t* hos = NULL;
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
    host_llist_t* cur = schemes[sch].list;
    schemes[sch].list = schemes[sch].initial;
    while(schemes[sch].list != NULL){
        if(schemes[sch].list->isInital == 1){
            schemes[sch].list = schemes[sch].list->next;
            continue;
        } 
        if(strcmp(host, schemes[sch].list->host.name) == 0){
            hos = schemes[sch].list;
            break;
        }
        
    }
    schemes[sch].list = cur;
    if(hos == NULL) return 2;
    hos->host.send_handler(data, size, path);
    return 0;
}


void* recv_from_url(char* url, uint64_t size){
    char scheme[NAMING_SIZE];
    char hostandpath[NAMING_SIZE + 1024];
    char host[NAMING_SIZE];
    char path[1024];
    int sch = -1;
    host_llist_t* hos = NULL;
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
    host_llist_t* cur = schemes[sch].list;
    schemes[sch].list = schemes[sch].initial;
    while(schemes[sch].list != NULL){
        if(schemes[sch].list->isInital == 1){
            schemes[sch].list = schemes[sch].list->next;
            continue;
        } 
        if(strcmp(host, schemes[sch].list->host.name) == 0){
            hos = schemes[sch].list;
        }
        schemes[sch].list = schemes[sch].list->next;
    }
    schemes[sch].list = cur;
    if(hos == NULL) return NULL;
    return hos->host.recv_handler(size, path);
}


host_llist_t* return_hosts_from_scheme(char* scheme){
    for(int i = 0; i <= curScheme; i++){
        if(strcmp(scheme, schemes[i].name) == 0){
            return schemes[i].initial;
        }
    }
    return NULL;
}