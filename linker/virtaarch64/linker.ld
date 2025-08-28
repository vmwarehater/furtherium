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
    . += 0x30000;
    sp_top = .;
}