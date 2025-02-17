build:
	# build bootstrap
	i686-elf-as src/bootstrap/bootstrap.asm -o bin/object/bootstrap.o
	# build kernel
	i686-elf-gcc -c src/kernel/kernel.c -o bin/object/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions
	# link all
	i686-elf-gcc -T src/linker/linker.ld -o bin/binary/os.bin -ffreestanding -O2 -nostdlib bin/object/bootstrap.o bin/object/kernel.o -lgcc

clean:
	rm -rf bin/binary/*
	rm -rf bin/object/*
	rm -rf bin/iso/*
	rm -rf bin/syslinux/*

iso:
	rm -rf bin/grub
	mkdir bin/grub/boot/grub -p
	cp bin/binary/os.bin bin/grub/boot/os.bin
	cp config/grub.cfg bin/grub/boot/grub
	
	grub-mkrescue -o bin/iso/system.iso bin/grub

start:
	qemu-system-i386 -kernel bin/binary/os.bin

startiso:
	qemu-system-i386 -cdrom bin/iso/system.iso
