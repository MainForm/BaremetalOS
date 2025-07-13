# Architecture of BCM2711 mounted to RaspberryPI 4
ARCH = armv8-a
MCPU = cortex-a72

# target board
TARGET_BOARD = raspberrypi4

# Compiler for aarch64
TOOLCHAIN_PREFIX = aarch64-none-elf
AS = $(TOOLCHAIN_PREFIX)-as
CC = $(TOOLCHAIN_PREFIX)-gcc
LD = $(TOOLCHAIN_PREFIX)-gcc
OBJCOPY = $(TOOLCHAIN_PREFIX)-objcopy

ASFLAG = -c -g
CFLAG  = -c -g -Wall -O2
# This options are for the bare metal environment
LDFLAG = -fno-builtin -ffreestanding -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector

INCLUDE_DIRS = -Iinclude -I$(BOARD_DIR)/include -Ilib/newlib/$(TOOLCHAIN_PREFIX)/include

SRC_DIR = src
BOARD_DIR = board/$(TARGET_BOARD)
BOARD_SRC_DIR = $(BOARD_DIR)/src

FIRMWARE_DIR = $(BOARD_DIR)/firmware

BUILD_DIR = build

AS_SRCS = $(shell find $(SRC_DIR) -name '*.S')
AS_OBJS = $(AS_SRCS:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.os)

C_SRCS = $(shell find $(SRC_DIR) -name '*.c')
C_OBJS = $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

BOARD_C_SRCS = $(shell find $(BOARD_SRC_DIR) -name '*.c')
BOARD_C_OBJS = $(BOARD_C_SRCS:$(BOARD_SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LD_SCRIPT = linker.ld

TARGET = image
ELF_FILE = kernel.elf

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(ELF_FILE)
	@mkdir -p $(BUILD_DIR)/output
	$(OBJCOPY) -O binary $(BUILD_DIR)/$< $(BUILD_DIR)/output/$@
	cp $(FIRMWARE_DIR)/* $(BUILD_DIR)/output/

$(ELF_FILE): $(AS_OBJS) $(C_OBJS) $(BOARD_C_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAG) -T $(LD_SCRIPT) -o $(BUILD_DIR)/$@ $^

$(AS_OBJS): $(BUILD_DIR)/%.os: $(SRC_DIR)/%.S
	@mkdir -p $(BUILD_DIR)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) $(ASFLAG) -o $@ $<

$(C_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(INCLUDE_DIRS) -o $@ $<

$(BOARD_C_OBJS): $(BUILD_DIR)/%.o: $(BOARD_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(INCLUDE_DIRS) -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
