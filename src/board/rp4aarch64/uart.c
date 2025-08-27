#include "../uart.h"
#include <stdint.h>




extern uint64_t MMIO_BASE;

// thanks to osdev.org for helping me with this!

enum
{
    GPIO_BASE = 0x200000,

    GPPUD = (GPIO_BASE + 0x94),

    GPPUDCLK0 = (GPIO_BASE + 0x98),

    UART0_BASE = (GPIO_BASE + 0x1000),

    UART0_DR     = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR     = (UART0_BASE + 0x18),
    UART0_ILPR   = (UART0_BASE + 0x20),
    UART0_IBRD   = (UART0_BASE + 0x24),
    UART0_FBRD   = (UART0_BASE + 0x28),
    UART0_LCRH   = (UART0_BASE + 0x2C),
    UART0_CR     = (UART0_BASE + 0x30),
    UART0_IFLS   = (UART0_BASE + 0x34),
    UART0_IMSC   = (UART0_BASE + 0x38),
    UART0_RIS    = (UART0_BASE + 0x3C),
    UART0_MIS    = (UART0_BASE + 0x40),
    UART0_ICR    = (UART0_BASE + 0x44),
    UART0_DMACR  = (UART0_BASE + 0x48),
    UART0_ITCR   = (UART0_BASE + 0x80),
    UART0_ITIP   = (UART0_BASE + 0x84),
    UART0_ITOP   = (UART0_BASE + 0x88),
    UART0_TDR    = (UART0_BASE + 0x8C),

    MBOX_BASE    = 0xB880,
    MBOX_READ    = (MBOX_BASE + 0x00),
    MBOX_STATUS  = (MBOX_BASE + 0x18),
    MBOX_WRITE   = (MBOX_BASE + 0x20)
};

void setup_uart(){
    // uart is now dead
    *(volatile uint32_t*)(MMIO_BASE + UART0_CR) = 0x00000000;
    *(volatile uint32_t*)(MMIO_BASE + GPPUD) = 0x00000000;
    *(volatile uint32_t*)(MMIO_BASE + GPPUDCLK0) = (1<<14) | (1<<15);
    *(volatile uint32_t*)(MMIO_BASE + UART0_ICR) = 0x7FF;
    *(volatile uint32_t*)(MMIO_BASE + UART0_IBRD) = 1;
    *(volatile uint32_t*)(MMIO_BASE + UART0_FBRD) = 1;
    *(volatile uint32_t*)(MMIO_BASE + UART0_FBRD) = 40;
    *(volatile uint32_t*)(MMIO_BASE + UART0_LCRH) = (1<<4) | (1<<5) | (1<<6);
    *(volatile uint32_t*)(MMIO_BASE + UART0_IMSC) = (1<<1) | (1<<4) | (1<<5) |
                                                    (1<<7) | (1<<8) | (1<<9) | (1<<10);
    *(volatile uint32_t*)(MMIO_BASE + UART0_CR) = (1<<0) | (1<<8) | (1<<9);
    return;
}

void write_to_uart(uint8_t c){
    while(*(volatile uint32_t*)(MMIO_BASE + UART0_FR) & (1<<5)){
        continue;
    }
    *(volatile uint32_t*)(MMIO_BASE + UART0_DR) = c;
}

uint8_t read_from_uart_without_blocking(){
    // STUB;
    return 0;
}

void write_string_to_uart(char* string){
    while(*string != '\0'){
        write_to_uart(*string);
        string++;
    }
}