#include "nearvm.h"
#include <stdint.h>
#include "../klibc/puts.h"
#include "../mem/chunkalloc.h"



uint64_t genreg[30] = {0};
uint64_t specreg[10] = {0};


typedef struct _func {
    uint64_t key;
    uint64_t curbycode;
    uint64_t prev_func;
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
    FUNC = 0x9,
    CMPE = 0xA,
    CMPL = 0xB,
    CMPG = 0xC,
    FUNCASKIP = 0xD,
    RET = 0xE
};

enum special_registers {
    FUNC_AM = 0,
    KILL_P = 1,
    PC = 2,
    PREV_PC = 3
};

static inline void add_ins(uint64_t* bytecode){
    if(bytecode[specreg[PC] + 1] >= 30 || bytecode[specreg[PC] + 2] >= 30
        || bytecode[specreg[PC] + 3] >= 30) return;
    genreg[bytecode[specreg[PC] + 1]] = genreg[bytecode[specreg[PC] + 2]] + genreg[bytecode[specreg[PC] + 3]];
}

static inline void sub_ins(uint64_t* bytecode){
    if(bytecode[specreg[PC] + 1] >= 30 || bytecode[specreg[PC] + 2] >= 30
        || bytecode[specreg[PC] + 3] >= 30) return;
    genreg[bytecode[specreg[PC] + 1]] = genreg[bytecode[specreg[PC] + 2]] - genreg[bytecode[specreg[PC] + 3]];
}

static inline void mul_ins(uint64_t* bytecode){
    if(bytecode[specreg[PC] + 1] >= 30 || bytecode[specreg[PC] + 2] >= 30
        || bytecode[specreg[PC] + 3] >= 30) return;
    genreg[bytecode[specreg[PC] + 1]] = genreg[bytecode[specreg[PC] + 2]] * genreg[bytecode[specreg[PC] + 3]];
}

static inline void div_ins(uint64_t* bytecode){
    if(bytecode[specreg[PC] + 1] >= 30 || bytecode[specreg[PC] + 2] >= 30
        || bytecode[specreg[PC] + 3] >= 30) return;
    genreg[bytecode[specreg[PC] + 1]] = genreg[bytecode[specreg[PC] + 2]] / genreg[bytecode[specreg[PC] + 3]];
}


static inline void mov_ins(uint64_t* bytecode){
    if(bytecode[specreg[PC] + 1] >= 30 || bytecode[specreg[PC] + 2] >= 30) return;
    genreg[bytecode[specreg[PC] + 1]] = bytecode[specreg[PC] + 2];
}

static inline void load_ins(uint64_t* bytecode){
    if(bytecode[specreg[PC] + 1] == (uint64_t)NULL || bytecode[specreg[PC] + 2] == (uint64_t)NULL) return;

}

static inline void store_ins(uint64_t* bytecode){
    if(bytecode[specreg[PC] + 1] == (uint64_t)NULL || bytecode[specreg[PC] + 2] == (uint64_t)NULL) return;

}

static inline void jump_ins(uint64_t* bytecode, func_t* stack){
    uint64_t val = specreg[PC];
    if(bytecode[val + 1] == (uint64_t)NULL) return;
    for(uint64_t i = 0; i < specreg[FUNC_AM]; i++){
        if(stack[i].key == bytecode[val + 1]){
            specreg[PREV_PC] = specreg[PC] + 2;
            specreg[PC] = stack[i].curbycode;
            return;
        }
    }
}

static inline void func_ins(uint64_t* bytecode, func_t* stack){
    if(bytecode[specreg[PC] + 1] == (uint64_t)NULL) return;
    if(specreg[FUNC_AM] * sizeof(uint64_t) >= 0x1000){
        puts("ERROR: stack has been filled, killing process to avoid stack overflow");
        specreg[KILL_P] = 1;
        return;
    }
    for(uint64_t i = 0; i < specreg[FUNC_AM]; i++){
        if(stack[i].key == bytecode[specreg[PC] + 1]){
            return;
        }
    }
    //(specreg[FUNC_AM] * sizeof(uint64_t));
    stack[specreg[FUNC_AM]].key = bytecode[specreg[PC] + 1];
    stack[specreg[FUNC_AM]].curbycode = specreg[PC] + 3;
    specreg[FUNC_AM]++;
}

static inline void func_ins_offset_1(uint64_t* bytecode, func_t* stack){
    if(bytecode[specreg[PC] + 1] == (uint64_t)NULL){
        return;
    } 
    if(specreg[FUNC_AM] * sizeof(uint64_t) >= 0x1000){
        puts("ERROR: stack has been filled, killing process to avoid stack overflow");
        specreg[KILL_P] = 1;
        return;
    }
    for(uint64_t i = 0; i < specreg[FUNC_AM]; i++){
        if(stack[i].key == bytecode[specreg[PC] + 1]){
            return;
        }
    }
    //(specreg[FUNC_AM] * sizeof(uint64_t));
    stack[specreg[FUNC_AM]].key = bytecode[specreg[PC] + 1];
    stack[specreg[FUNC_AM]].curbycode = specreg[PC] + 3;

    specreg[FUNC_AM]++;
}

static inline void kernel_call_ins(){
    switch (genreg[0]) {
        case 0:
            xputs_a("kernel call", genreg[1]);
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

static inline void compare_less_then_ins(uint64_t* bytecode, func_t* stack){
    uint64_t val = specreg[PC];
    if(bytecode[val + 1] >= 30 || bytecode[val + 2] >= 30) return;
    if(genreg[bytecode[val + 1]] >= genreg[bytecode[val + 2]]){
        specreg[PC] += 4;
        return;
    } 
    if(bytecode[val + 3] == (uint64_t)NULL) return;
    for(uint64_t i = 0; i < specreg[FUNC_AM]; i++){
        if(stack[i].key == bytecode[val + 3]){
            specreg[PREV_PC] = specreg[PC] + 4;
            specreg[PC] = stack[i].curbycode;
            return;
        }
    }
}

static inline void compare_greater_then_ins(uint64_t* bytecode, func_t* stack){
    uint64_t val = specreg[PC];
    if(bytecode[val + 1] >= 30 || bytecode[val + 2] >= 30) return;
    if(genreg[bytecode[val + 1]] <= genreg[bytecode[val + 2]]){
        specreg[PC] += 4;
        return;
    } 
    if(bytecode[val + 3] == (uint64_t)NULL) return;
    for(uint64_t i = 0; i < specreg[FUNC_AM]; i++){
        if(stack[i].key == bytecode[val + 3]){
            specreg[PREV_PC] = specreg[PC] + 4;
            specreg[PC] = stack[i].curbycode;
            
            return;
        }
    }
}

static inline void compare_equal_to_ins(uint64_t* bytecode, func_t* stack){
    uint64_t val = specreg[PC];
    if(bytecode[val + 1] >= 30 || bytecode[val + 2] >= 30) return;
    if(genreg[bytecode[val + 1]] != genreg[bytecode[val + 2]]){
        specreg[PC] += 4;
        return;
    } 
    if(bytecode[val + 3] == (uint64_t)NULL) return;
    for(uint64_t i = 0; i < specreg[FUNC_AM]; i++){
        if(stack[i].key == bytecode[val + 3]){
            specreg[PREV_PC] = specreg[PC] + 4;
            specreg[PC] = stack[i].curbycode;
            return;
        }
    }
}

static inline void func_and_skip_ins(uint64_t* bytecode, func_t* stack){
    uint64_t val = specreg[PC];
    func_ins_offset_1(bytecode, stack);

    for(int i = 0; i <= bytecode[val + 2]; i++){
        if(bytecode[specreg[PC]] == NULL){
            puts("ERROR! OVERFLOW");
            specreg[KILL_P] = 1;
            return;
        }

        switch(bytecode[specreg[PC]]){
            case ADD:
                specreg[PC] += 4;
                break;
            case SUB:
                specreg[PC] += 4;
                break;
            case MOV:
                specreg[PC] += 3;
                break;
            case LD:
                specreg[PC] += 3;
                break;
            case STR:
                specreg[PC] += 3;
                break;
            case JMP:
                specreg[PC] += 2;
                break;
            case KCALL:
                specreg[PC] += 1;
                break;
            case MUL:
                specreg[PC] += 4;
                break;
            case DIV:
                specreg[PC] += 4;
                break;
            case FUNC:
                specreg[PC] += 2;
                break;
            case CMPE:
                specreg[PC] += 3;
                break;
            case FUNCASKIP:
                specreg[PC] += 3;
                break;
            case RET:
                specreg[PC] += 1;
                break;
            default:
                break;
        }
    }
}

static inline void return_ins(){
    specreg[PC] = specreg[PREV_PC];
}

void interpret_vm_bytecode(uint64_t* bytecode){
    uint8_t run = 1;
    func_t* stack = allocate_multiple_chunks(4); // 4Kbs
    while(run == 1){
        if(specreg[KILL_P] == 1 || !bytecode[specreg[PC]]){
            goto EXIT;
        } 
        //xputs(specreg[PC]);
        switch(bytecode[specreg[PC]]){
            case ADD:
                add_ins(bytecode);
                specreg[PC] += 4;
                break;
            case SUB:
                sub_ins(bytecode);
                specreg[PC] += 4;
                break;
            case MOV:
                mov_ins(bytecode);
                specreg[PC] += 3;
                break;
            case LD:
                load_ins(bytecode);
                break;
            case STR:
                store_ins(bytecode);
                break;
            case JMP:
                jump_ins(bytecode, stack);
                break;
            case KCALL:
                kernel_call_ins();
                specreg[PC] += 1;
                break;
            case MUL:
                mul_ins(bytecode);
                specreg[PC] += 4;
                break;
            case DIV:
                div_ins(bytecode);
                specreg[PC] += 4;
                break;
            case FUNC:
                func_ins(bytecode, stack);
                specreg[PC] += 2;
                break;
            case CMPE:
                compare_equal_to_ins(bytecode, stack);
                break;
            case CMPL:
                compare_less_then_ins(bytecode, stack);
                break;
            case CMPG:
                compare_greater_then_ins(bytecode, stack);
                break;
            case FUNCASKIP:
                func_and_skip_ins(bytecode, stack);
                break;
            case RET:
                return_ins();
                break;
            default:
                goto EXIT;
                break;
        }
    }
    EXIT:
    free_multiple_chunks(stack, 4);
}