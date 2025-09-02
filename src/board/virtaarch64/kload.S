.global loader_entry






loader_entry:
    ic IALLUIS
    isb
    mrs x0, SCTLR_EL1
    bic x0, x0, (1 << 0)
    bic x0, x0, (1 << 2)
    bic x0, x0, (1 << 12)
    bic x0, x0, (1 << 11)
    msr SCTLR_EL1, x0
    isb
    ldr x30, =sp_top
    mov sp, x30
    bl kernel_entry
    b .