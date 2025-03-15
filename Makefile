AS = i686-elf-as
CC = i686-elf-gcc
LD = $(CC)

ASFLAGS =
CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -g
LDFLAGS = -ffreestanding -O2 -nostdlib

BUILD_DIR = build

SRC_DIR = src
OBJ_DIR = $(BUILD_DIR)/object
BIN_DIR = $(BUILD_DIR)/binary

#SRC_BOOTSTRAP_ASM = $(SRC_DIR)/bootstrap/bootstrap.asm
SRC_ASM = $(shell find $(SRC_DIR) -name "*.asm")
SRC_C = $(shell find $(SRC_DIR) -name "*.c")
SRC_LD = $(SRC_DIR)/linker.ld

OBJ_ASM = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_ASM:.asm=.o))
OBJ_C = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_C:.c=.o))

TARGET = $(BIN_DIR)/os.bin
TARGET_ELF = $(BIN_DIR)/os.elf

INCLUDE = -Isrc -Isrc/arch/i386

all: $(TARGET)
elf: $(TARGET_ELF)

# build kernel c files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

# build kernel asm files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(TARGET_ELF): $(OBJ_ASM) $(OBJ_C) | $(BIN_DIR)
	$(LD) -T $(SRC_LD) -o $@ $(LDFLAGS) $^ -lgcc

$(TARGET): $(OBJ_ASM) $(OBJ_C) | $(BIN_DIR)
	$(LD) -T $(SRC_LD) -o $@ $(LDFLAGS) $^ -lgcc

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(BUILD_DIR)/grub
	rm -rf $(BUILD_DIR)/iso/*

iso:
	rm -rf $(BUILD_DIR)/grub
	mkdir $(BUILD_DIR)/grub/boot/grub -p
	cp $(BUILD_DIR)/binary/os.bin $(BUILD_DIR)/grub/boot/os.bin
	cp config/grub.cfg $(BUILD_DIR)/grub/boot/grub
	grub-mkrescue -o $(BUILD_DIR)/iso/system.iso bin/grub

start:
	qemu-system-x86_64 -kernel $(TARGET)

dev:
	make elf
	@echo
	@echo '[!] use `gdb -ex "target remote localhost:2222" -ex "symbol-file $(shell pwd)/bin/binary/os.elf"` to debug'
	@echo
	qemu-system-x86_64 -kernel $(TARGET_ELF) -S -gdb tcp::2222


.PHONY: all elf
