#include "nearvm.h"
#include <stdint.h>
#include "../klibc/puts.h"




uint64_t genreg[30] = {0};


enum instructions {
    ADD = 0x0,
    SUB = 0x1,
    MOV = 0x2,
    LD = 0x3,
    STR = 0x4,
    JMP = 0x5,
    KCALL = 0x6,
    MUL = 0x7,
    DIV = 0x8
};


static inline void add_ins(uint64_t* bytecode){
    if(bytecode[1] >= 30 || bytecode[2] >= 30
        || bytecode[3] >= 30) return;
    genreg[bytecode[1]] = genreg[bytecode[2]] + genreg[bytecode[3]];
}

static inline void sub_ins(uint64_t* bytecode){
    if(bytecode[1] >= 30 || bytecode[2] >= 30
        || bytecode[3] >= 30) return;
    genreg[bytecode[1]] = genreg[bytecode[2]] - genreg[bytecode[3]];
}

static inline void mul_ins(uint64_t* bytecode){
    if(bytecode[1] >= 30 || bytecode[2] >= 30
        || bytecode[3] >= 30) return;
    genreg[bytecode[1]] = genreg[bytecode[2]] * genreg[bytecode[3]];
}

static inline void div_ins(uint64_t* bytecode){
    if(bytecode[1] >= 30 || bytecode[2] >= 30
        || bytecode[3] >= 30) return;
    genreg[bytecode[1]] = genreg[bytecode[2]] / genreg[bytecode[3]];
}


static inline void mov_ins(uint64_t* bytecode){
    if(bytecode[1] >= 30 || bytecode[2] >= 30) return;
    genreg[bytecode[1]] = bytecode[2];
}

static inline void load_ins(uint64_t* bytecode){
    if(bytecode[1] == (uint64_t)NULL || bytecode[2] == (uint64_t)NULL) return;

}

static inline void store_ins(uint64_t* bytecode){
    if(bytecode[1] == (uint64_t)NULL || bytecode[2] == (uint64_t)NULL) return;

}

static inline void jump_ins(uint64_t* bytecode){
    if(bytecode[1] == (uint64_t)NULL || bytecode[2] == (uint64_t)NULL) return;

}

static inline void kernel_call_ins(uint64_t* bytecode){
    switch (genreg[0]) {
        case 0:
            xputs(genreg[1]);
            break;
        case 1: {
            char* string = (char*)genreg[1];
            puts(string);
            break;
        }
        default:
            break;
    }
}


void interpret_vm_bytecode_line(uint64_t* bytecode){
    switch(bytecode[0]){
        case ADD:
            add_ins(bytecode);
            break;
        case SUB:
            sub_ins(bytecode);
            break;
        case MOV:
            mov_ins(bytecode);
            break;
        case LD:
            load_ins(bytecode);
            break;
        case STR:
            store_ins(bytecode);
            break;
        case JMP:
            jump_ins(bytecode);
            break;
        case KCALL:
            kernel_call_ins(bytecode);
            break;
        case MUL:
            mul_ins(bytecode);
            break;
        case DIV:
            div_ins(bytecode);
            break;
        default:
            // in here call INVALID_BYTECODE signal to the process which called it
            // we don't have that infra yet so its a note for when we do implement it
            break;
    }
}

// multi-line bytecode interperter
// TODO, implement this **correctly**
void interpret_vm_bytecode(uint64_t* bytecode){
    switch(bytecode[0]){
        case ADD:
            add_ins(bytecode);
            break;
        case SUB:
            sub_ins(bytecode);
            break;
        case MOV:
            mov_ins(bytecode);
            break;
        case LD:
            load_ins(bytecode);
            break;
        case STR:
            store_ins(bytecode);
            break;
        case JMP:
            jump_ins(bytecode);
            break;
        case KCALL:
            kernel_call_ins(bytecode);
            break;
        case MUL:
            mul_ins(bytecode);
            break;
        case DIV:
            div_ins(bytecode);
            break;
        default:
            // in here call INVALID_BYTECODE signal to the process which called it
            // we don't have that infra yet so its a note for when we do implement it
            break;
    }
}