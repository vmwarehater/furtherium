.global loader_entry






loader_entry:
    ldr x30, =sp_top
    mov sp, x30
    bl kernel_entry
    b .