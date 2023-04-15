DIR = $(shell pwd)
CC := gcc
CFLAGS := -I kernel/include -O3 -nostdlib -m32 -march=i386 -fno-pie -fno-stack-protector -ffreestanding
LD := ld
LDFLAGS := -m elf_i386 -T $(DIR)/linker.ld -nostdlib
ASM := nasm

.PHONY: all build clean qemu rebuild

all: build qemu

build:
	@echo "> Compiling libs and kernel..."
	@make --no-print-directory -C ./kernel
	@echo ">  Linking libs and kernel..."
	@echo "-    Linking $(shell find . -type f -name "*.o") $(shell find . -type f -name "*.o") to ./build/bin/kernel.bin"
	@$(LD) $(LDFLAGS) --oformat binary $(shell find ./build -type f -name "*.o") $(shell find ./build -type f -name "*.oasm") -o $(DIR)/build/bin/kernel.bin
	@echo ">  Assembling bootloader..."
	@nasm ./boot/boot.asm -f bin -o ./build/bin/boot.bin
	@echo ">  Creating disk image..."
	@cat build/bin/boot.bin build/bin/kernel.bin > build/img/disk.img

clean:
	rm -rf build
	mkdir -p build/kernel/ build/bin/ build/img/

qemu:
	@qemu-system-x86_64 -fda build/img/disk.img

rebuild: clean build
