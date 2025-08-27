

target("aarch64-virt")
    set_toolchains("clangk")
    set_kind("binary")
    set_targetdir(".")
    set_filename("furtherk.elf")
    add_files("src/*.c")
    add_files("src/system/*.c", "src/system/**/.c")
    add_files("src/arch/aarch64/*.c", "src/arch/aarch64/*.S")
    add_files("src/board/virtaarch64/*.c", "src/board/virtaarch64/*.S")
    add_cflags("--target=aarch64-none-elf -ffreestanding", {force = true})
    add_asflags("--target=aarch64-none-elf -ffreestanding -nostdlib -fno-rtti", {force = true})
    add_ldflags("-nostdlib -T linker/virtaarch64/linker.ld", {force = true})


target("stub")
    set_toolchains("clangk")
    set_kind("binary")
    set_targetdir(".")
    set_filename("furtherk.elf")
    add_files("src/*.c")
    add_files("src/system/*.c", "src/system/**/.c")
    add_files("src/arch/stub/*.c", "src/arch/stub/*.S")
    add_files("src/board/stub/*.c", "src/board/stub/*.S")
    -- we will never use MIPS so I decided to choose that architecture
    -- for the stub
    -- (if anyone ever does make a MIPS port lmk and remove this)
    add_cflags("--target=mips-none-elf -ffreestanding", {force = true})
    add_asflags("--target=mips-none-elf -ffreestanding -nostdlib -fno-rtti", {force = true})
    add_ldflags("-nostdlib -T linker/stub/linker.ld", {force = true})




toolchain("clangk")
    set_kind("standalone")
    set_toolset("cc", "clang");
    set_toolset("as", "clang");
    set_toolset("ld", "ld.lld")
toolchain_end();