run-aarch64:
	qemu-system-aarch64 -machine virt -cpu cortex-a57 -kernel furtherk.elf \
		-serial mon:stdio -display sdl
		
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
	@echo if you see this everything was successful!


