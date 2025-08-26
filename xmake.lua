set_project("furtherk")


target("furtherk")
    set_toolchains("clangaarch")
    set_kind("binary")
    set_targetdir(".")
    set_filename("furtherk.elf")
    add_files("src/*.c", "src/**/*.c")
    add_files("src/*.S", "src/**/*.S")
    add_cflags("--target=aarch64-none-elf -ffreestanding", {force = true})
    add_asflags("--target=aarch64-none-elf -ffreestanding -nostdlib -fno-rtti", {force = true})
    add_ldflags("-nostdlib -T linker.ld", {force = true})





toolchain("clangaarch")
    set_kind("standalone")
    set_toolset("cc", "clang");
    set_toolset("as", "clang");
    set_toolset("ld", "ld.lld")
toolchain_end();