#ifndef CHUNKALLOC_H_INCLUDED
#define CHUNKALLOC_H_INCLUDED












#include <stdint.h>




void chunk_allocator_setup();
void* allocate_single_chunk();
void* allocate_multiple_chunks(uint64_t amount);
void free_single_chunk(void* address);
void free_multiple_chunks(void* address, uint64_t amount);





#endif




