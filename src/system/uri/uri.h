#ifndef URI_H_INCLUDED
#define URI_H_INCLUDED












#include <stdint.h>
#include <stddef.h>


#define NAMING_SIZE 20


typedef struct _host {
    char name[NAMING_SIZE];
    void (*send_handler)(void* data, size_t size, char* path);
    void* (*recv_handler)(size_t data, char* path);
} host_t;

typedef struct _host_llist {
    host_t host;
    uint8_t isInital;
    struct _host_llist* prev;
    struct _host_llist* next;
} host_llist_t;

uint8_t create_scheme(char* scheme_name);
uint8_t create_host(char* scheme_name, host_t host);
uint8_t send_to_url(char* url, void* data, uint64_t size);
void* recv_from_url(char* url, uint64_t size);
host_llist_t* return_hosts_from_scheme(char* scheme);

#endif