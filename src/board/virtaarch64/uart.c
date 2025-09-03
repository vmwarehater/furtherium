#include "../uart.h"
#include <stdint.h>



// thanks to https://krinkinmu.github.io/2020/11/29/PL011.html for helping me with this!

#define UART_ADDRESS 0x09000000

#define DR_OFFSET 0x000
#define FR_OFFSET 0x018
#define IBRD_OFFSET 0x024
#define FBRD_OFFSET 0x028
#define LCR_OFFSET 0x02c
#define CR_OFFSET 0x030
#define IMSC_OFFSET 0x038
#define DMACR_OFFSET 0x048


#define FR_BUSY (1 << 3)
#define CR_TXEN (1 << 8)
#define CR_UARTEN (1 << 0)
#define LCR_FEN (1 << 4)
#define LCR_STP2 (1 << 3)

static uint64_t base_clock = 0;
static uint32_t baudrate = 0;
static uint32_t data_bits = 0;
static uint32_t stop_bits = 0;

static inline volatile uint32_t* reg(uint32_t offset){
    return (volatile uint32_t*)UART_ADDRESS + offset;
}

static inline volatile uint8_t* reg8(uint32_t offset){
    return (volatile uint8_t*)UART_ADDRESS + offset;
}

static inline void calculate_divisors(uint32_t* integer, uint32_t* frac){
    uint32_t div = 4 * base_clock / baudrate;

    *frac = div & 0x3f;
    *integer = (div >> 6) & 0xffff;
}

static inline void wait_tx_complete(){
    while((*reg(FR_OFFSET) * FR_BUSY) != 0){continue;}
}

static inline void reset(){
    uint32_t cr = *reg(CR_OFFSET);
    uint32_t lcr = *reg(LCR_OFFSET);
    uint32_t ibrd, fbrd;

    *reg(CR_OFFSET) = (cr & CR_UARTEN);
    wait_tx_complete();

    *reg(LCR_OFFSET) = (lcr & ~LCR_FEN);

    calculate_divisors(&ibrd, &fbrd);
    *reg(IBRD_OFFSET) = ibrd;
    *reg(FBRD_OFFSET) = fbrd;

    lcr = 0x0;

    lcr |= ((data_bits - 1) & 0x3) << 5;

    if(stop_bits == 2) lcr |= LCR_STP2;
    *reg(IMSC_OFFSET) = 0x7ff;
    *reg(DMACR_OFFSET) = 0x0;
    *reg(CR_OFFSET) = CR_TXEN;
    *reg(CR_OFFSET) = CR_TXEN | CR_UARTEN;
}

void setup_uart(){
    base_clock = 24000000;
    baudrate = 115200;
    data_bits = 8;
    stop_bits = 1;
    reset();
    return;
}

void write_to_uart(uint8_t c){
    wait_tx_complete();
    *reg(DR_OFFSET) = c;
    //*(volatile uint8_t*)UART_ADDRESS = c;
}

uint8_t read_from_uart_without_blocking(){
    return *reg(DR_OFFSET);
}

uint8_t read_from_uart(){
    // TODO: make the 0x18 offset a define with a name
    while(*reg8(0x18) & (1 << 4));
    return *reg(DR_OFFSET);
}

void write_string_to_uart(char* string){
    while(*string != '\0'){
        write_to_uart(*string);
        string++;
    }
}