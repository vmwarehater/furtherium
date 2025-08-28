#ifndef URI_H_INCLUDED
#define URI_H_INCLUDED












#include <stdint.h>
#include <stddef.h>


#define NAMING_SIZE 20


typedef struct _host {
    char name[NAMING_SIZE];
    void (*SendHandler)(void* data, size_t size, char* path);
    void* (*RecvHandler)(size_t data, char* path);
} host_t;

uint8_t create_scheme(char* scheme_name);
uint8_t create_host(char* scheme_name, host_t host);
uint8_t send_to_url(char* url, void* data, uint64_t size);



#endif