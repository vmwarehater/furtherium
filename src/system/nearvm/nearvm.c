#include "nearvm.h"
#include <stdint.h>
#include "../klibc/puts.h"
#include "../mem/chunkalloc.h"



uint64_t genreg[30] = {0};
uint64_t specreg[10] = {0};


typedef struct _func {
    uint64_t key;
    uint64_t curbycode;
} func_t;
enum instructions {
    ADD = 0x0,
    SUB = 0x1,
    MOV = 0x2,
    LD = 0x3,
    STR = 0x4,
    JMP = 0x5,
    KCALL = 0x6,
    MUL = 0x7,
    DIV = 0x8,
    FUNC = 0x9
};

enum SPECIAL_REGISTERS {
    FUNC_AM = 0
};

static inline void add_ins(uint64_t* bytecode, uint64_t cur_reg){
    if(bytecode[cur_reg + 1] >= 30 || bytecode[cur_reg + 2] >= 30
        || bytecode[cur_reg + 3] >= 30) return;
    genreg[bytecode[cur_reg + 1]] = genreg[bytecode[cur_reg + 2]] + genreg[bytecode[cur_reg + 3]];
}

static inline void sub_ins(uint64_t* bytecode, uint64_t cur_reg){
    if(bytecode[cur_reg + 1] >= 30 || bytecode[cur_reg + 2] >= 30
        || bytecode[cur_reg + 3] >= 30) return;
    genreg[bytecode[cur_reg + 1]] = genreg[bytecode[cur_reg + 2]] - genreg[bytecode[cur_reg + 3]];
}

static inline void mul_ins(uint64_t* bytecode, uint64_t cur_reg){
    if(bytecode[cur_reg + 1] >= 30 || bytecode[cur_reg + 2] >= 30
        || bytecode[cur_reg + 3] >= 30) return;
    genreg[bytecode[cur_reg + 1]] = genreg[bytecode[cur_reg + 2]] * genreg[bytecode[cur_reg + 3]];
}

static inline void div_ins(uint64_t* bytecode, uint64_t cur_reg){
    if(bytecode[cur_reg + 1] >= 30 || bytecode[cur_reg + 2] >= 30
        || bytecode[cur_reg + 3] >= 30) return;
    genreg[bytecode[cur_reg + 1]] = genreg[bytecode[cur_reg + 2]] / genreg[bytecode[cur_reg + 3]];
}


static inline void mov_ins(uint64_t* bytecode, uint64_t cur_reg){
    if(bytecode[cur_reg + 1] >= 30 || bytecode[cur_reg + 2] >= 30) return;
    genreg[bytecode[cur_reg + 1]] = bytecode[cur_reg + 2];
}

static inline void load_ins(uint64_t* bytecode, uint64_t cur_reg){
    if(bytecode[cur_reg + 1] == (uint64_t)NULL || bytecode[cur_reg + 2] == (uint64_t)NULL) return;

}

static inline void store_ins(uint64_t* bytecode, uint64_t cur_reg){
    if(bytecode[cur_reg + 1] == (uint64_t)NULL || bytecode[cur_reg + 2] == (uint64_t)NULL) return;

}

static inline void jump_ins(uint64_t* bytecode, func_t* stack, uint64_t* cur_reg){
    uint64_t val = *cur_reg;
    if(bytecode[val + 1] == (uint64_t)NULL) return;
    for(uint64_t i = 0; i >= specreg[FUNC_AM]; i++){
        if(stack[i].key == bytecode[val + 1]){
            *cur_reg = stack[i].curbycode;
            return;
        }
    }
}

static inline void func_ins(uint64_t* bytecode, func_t* stack, uint64_t cur_reg){
    if(bytecode[cur_reg + 1] == (uint64_t)NULL) return;
    if(specreg[FUNC_AM] * sizeof(uint64_t) >= 0x1000){
        return;
    }
    puts("called again");
    stack[specreg[FUNC_AM]].key = bytecode[cur_reg + 1];
    stack[specreg[FUNC_AM]].curbycode = cur_reg;
}

static inline void kernel_call_ins(){
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


void interpret_vm_bytecode(uint64_t* bytecode){
    uint8_t run = 1;
    uint64_t curbycode = 0;
    func_t* stack = allocate_multiple_chunks(4); // 4Kbs
    while(run == 1){
        if(!bytecode[curbycode]) return;
        switch(bytecode[curbycode]){
            case ADD:
                add_ins(bytecode, curbycode);
                curbycode += 4;
                break;
            case SUB:
                sub_ins(bytecode, curbycode);
                curbycode += 4;
                break;
            case MOV:
                mov_ins(bytecode, curbycode);
                curbycode += 3;
                break;
            case LD:
                load_ins(bytecode, curbycode);
                break;
            case STR:
                store_ins(bytecode, curbycode);
                break;
            case JMP:
                jump_ins(bytecode, stack, &curbycode);
                curbycode += 2;
                break;
            case KCALL:
                kernel_call_ins();
                curbycode += 1;
                break;
            case MUL:
                mul_ins(bytecode, curbycode);
                curbycode += 4;
                break;
            case DIV:
                div_ins(bytecode, curbycode);
                curbycode += 4;
                break;
            case FUNC:
                func_ins(bytecode, stack, curbycode);
                curbycode += 2;
                break;
            default:
                break;
        }
    }
    free_multiple_chunks(stack, 4);
    
}

void interpret_vm_bytecode_line(uint64_t* bytecode){
    switch(bytecode[0]){
        case ADD:
            add_ins(bytecode, 0);
            break;
        case SUB:
            sub_ins(bytecode, 0);
            break;
        case MOV:
            mov_ins(bytecode, 0);
            break;
        case LD:
            load_ins(bytecode, 0);
            break;
        case STR:
            store_ins(bytecode, 0);
            break;
        case KCALL:
            kernel_call_ins();
            break;
        case MUL:
            mul_ins(bytecode, 0);
            break;
        case DIV:
            div_ins(bytecode, 0);
            break;
        default:
            // in here call INVALID_BYTECODE signal to the process which called it
            // we don't have that infra yet so its a note for when we do implement it
            break;
    }
}