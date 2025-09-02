ENTRY(loader_entry)

SECTIONS {
    . = 0x20000;
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
    . += 0x30000;
    sp_top = .;
}