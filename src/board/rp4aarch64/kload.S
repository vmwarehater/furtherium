.global loader_entry






loader_entry:
    mrs x0, SCTLR_EL1
    orr x0, x0, (1 << 0)
    orr x0, x0, (1 << 2)
    orr x0, x0, (1 << 12)
    msr SCTLR_EL1, x0
    isb
    ldr x30, =__start
    mov sp, x30

//     // bss cleanup bc this is required sadly
//     ldr x5, =__bss_start
//     ldr w6, =__bss_size
//     cbz w6, 2f
// 1:
//     str xzr, [x5], #8
//     sub w6, w6, #1
//     cbnz w6, 1b


2:
    bl kernel_entry
    b .