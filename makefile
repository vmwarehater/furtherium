run:
	qemu-system-aarch64 -machine virt -cpu cortex-a57 -kernel furtherk.elf \
		-serial mon:stdio -device ramfb -display sdl


clean:
	rm -rf .xmake
	rm -rf build
	rm furtherk.elf



test:
	xmake
	make run