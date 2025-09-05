run-aarch64-virt:
	qemu-system-aarch64 -machine virt -cpu cortex-a57 -kernel furtherk.elf -m 512M \
		-serial mon:stdio -display sdl

run-aarch64-rp4:
	qemu-system-aarch64 -M raspi4b -serial mon:stdio -kernel furtherk.elf
	
clean:
	rm -rf .xmake
	rm -rf build
	rm furtherk.elf


test-all:
	make clean
	@echo Building aarch64-virt
	xmake build aarch64-virt
	@echo Building Stub
	xmake build stub
	@echo Building aarch64-rp4
	xmake build aarch64-rp4
	@echo if you see this everything was successful!


