.global load_exception_vector
.extern exception_unimplemented
.extern exception_error


load_exception_vector:
    sub sp, sp, #16

    ldr x2, =exception_vector 
    msr VBAR_EL1, x2

    add sp, sp, #16
    ret


exception_vector:
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_error
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented
.balign 0x80
    bl exception_unimplemented


