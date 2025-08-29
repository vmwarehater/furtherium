#ifndef CHUNKALLOC_H_INCLUDED
#define CHUNKALLOC_H_INCLUDED












#include <stdint.h>





void* allocate_single_chunk();
void free_single_chunk(void* address);
void chunk_allocator_setup();





#endif




