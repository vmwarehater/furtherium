ENTRY(loader_entry)

SECTIONS {
    . = 0x40100000;
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
    . = ALIGN(8);
    . += 0x2000;
    sp_top = .;
}