.global loader_entry






loader_entry:
    ldr x30, =sp_top
    mov sp, x30
    mrs x0, SCTLR_EL1
    orr x0, x0, (1 << 0)
    orr x0, x0, (1 << 2)
    orr x0, x0, (1 << 12)
    msr SCTLR_EL1, x0
    isb
    bl kernel_entry
    b .