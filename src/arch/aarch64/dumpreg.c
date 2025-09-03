#include <stdint.h>
#include "../../system/klibc/puts.h"





typedef struct _registers {
    uint64_t x0;
    uint64_t x1;
    uint64_t x2;
    uint64_t x3;
    uint64_t x4;
    uint64_t x5;
    uint64_t x6;
    uint64_t x7;
    uint64_t x8;
    uint64_t x9;
    uint64_t x10;
    uint64_t x11;
    uint64_t x12;
    uint64_t x13;
    uint64_t x14;
    uint64_t x15;
    uint64_t x16;
    uint64_t x17;
    uint64_t x18;
    uint64_t fp;
    uint64_t lr;
    uint64_t xzr;
    uint64_t esr;
    uint64_t far;
} registers_t;



void print_registers(void* dump){
    registers_t* reg = (registers_t*)dump;
    puts("-------------------[Dumping CPU Registers]-------------------");
    puts_no_newline("x0: ");
    xputs(reg->x0);
    puts_no_newline("x1: ");
    xputs(reg->x1);
    puts_no_newline("x2: ");
    xputs(reg->x2);
    puts_no_newline("x3: ");
    xputs(reg->x3);
    puts_no_newline("x4: ");
    xputs(reg->x4);
    puts_no_newline("x5: ");
    xputs(reg->x5);
    puts_no_newline("x6: ");
    xputs(reg->x6);
    puts_no_newline("x7: ");
    xputs(reg->x7);
    puts_no_newline("x8: ");
    xputs(reg->x8);
    puts_no_newline("x9: ");
    xputs(reg->x9);
    puts_no_newline("x10: ");
    xputs(reg->x10);
    puts_no_newline("x11: ");
    xputs(reg->x11);
    puts_no_newline("x12: ");
    xputs(reg->x12);
    puts_no_newline("x13: ");
    xputs(reg->x13);
    puts_no_newline("x14: ");
    xputs(reg->x14);
    puts_no_newline("x15: ");
    xputs(reg->x15);
    puts_no_newline("x16: ");
    xputs(reg->x16);
    puts_no_newline("x17: ");
    xputs(reg->x17);
    puts_no_newline("x18: ");
    xputs(reg->x18);
    puts_no_newline("fp: ");
    xputs(reg->fp);
    puts_no_newline("lr: ");
    xputs(reg->lr);
    puts_no_newline("xzr: ");
    xputs(reg->xzr);
    puts_no_newline("esr: ");
    xputs(reg->esr);
    puts_no_newline("far: ");
    xputs(reg->far);
    puts("-----------------------[Finished Dump]-----------------------");
}