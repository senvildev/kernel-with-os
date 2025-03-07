AS = i686-elf-as
CC = i686-elf-gcc
LD = $(CC)

ASFLAGS =
CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -g
LDFLAGS = -ffreestanding -O2 -nostdlib

SRC_DIR = src
OBJ_DIR = bin/object
BIN_DIR = bin/binary

SRC_BOOTSTRAP_ASM = $(SRC_DIR)/bootstrap/bootstrap.asm
SRC_ASM = $(shell find $(SRC_DIR)/kernel -name "*.asm")
SRC_C = $(shell find $(SRC_DIR)/kernel -name "*.c")
SRC_LD = $(SRC_DIR)/linker/linker.ld

OBJ_BOOTSTRAP_ASM = $(OBJ_DIR)/bootstrap.o
OBJ_ASM = $(patsubst $(SRC_DIR)/kernel/%, $(OBJ_DIR)/%, $(SRC_ASM:.asm=.o))
OBJ_C = $(patsubst $(SRC_DIR)/kernel/%, $(OBJ_DIR)/%, $(SRC_C:.c=.o))

TARGET = $(BIN_DIR)/os.bin
TARGET_ELF = $(BIN_DIR)/os.elf

INCLUDE = -I./src/kernel

all: $(TARGET)
elf: $(TARGET_ELF)

# build kernel files (and c code)
$(OBJ_DIR)/%.o: $(SRC_DIR)/kernel/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

# build bootstrap (and assembly code)
$(OBJ_DIR)/bootstrap.o: $(SRC_BOOTSTRAP_ASM) | $(OBJ_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/kernel/%.asm | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(TARGET_ELF): $(OBJ_BOOTSTRAP_ASM) $(OBJ_ASM) $(OBJ_C) | $(BIN_DIR)
	$(LD) -T $(SRC_LD) -o $@ $(LDFLAGS) $^ -lgcc

$(TARGET): $(OBJ_BOOTSTRAP_ASM) $(OBJ_ASM) $(OBJ_C) | $(BIN_DIR)
	$(LD) -T $(SRC_LD) -o $@ $(LDFLAGS) $^ -lgcc

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf bin/grub

iso:
	rm -rf bin/grub
	mkdir bin/grub/boot/grub -p
	cp bin/binary/os.bin bin/grub/boot/os.bin
	cp config/grub.cfg bin/grub/boot/grub
	grub-mkrescue -o bin/iso/system.iso bin/grub

start:
	qemu-system-x86_64 -kernel $(TARGET)

dev:
	make elf
	@echo
	@echo '[!] use `gdb -ex "target remote localhost:2222" -ex "symbol-file $(shell pwd)/bin/binary/os.elf"` to debug'
	@echo
	qemu-system-x86_64 -kernel $(TARGET_ELF) -S -gdb tcp::2222


.PHONY: all elf
