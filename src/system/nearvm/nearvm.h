#ifndef NEARVM_H_INCLUDED
#define NEARVM_H_INCLUDED










#include <stdint.h>
#include <stddef.h>





void interpret_vm_bytecode_line(uint64_t* bytecode);
void interpret_vm_bytecode(uint64_t* bytecode);










#endif