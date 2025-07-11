# Architecture of BCM2711 mounted to RaspberryPI 4
ARCH = armv8-a
MCPU = cortex-a72

# Compiler for aarch64
AS = aarch64-linux-gnu-as
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

SRC_DIR = src
BUILD_DIR = build
AS_SRCS = $(shell find $(SRC_DIR) -name '*.S')
AS_OBJS = $(AS_SRCS:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.os)

C_SRCS = $(shell find $(SRC_DIR) -name '*.c')
C_OBJS = $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LD_SCRIPT = linker.ld

ASFLAG = -c -g
CFLAG = -c -g -Wall -O0

INCLUDE_DIRS = -Iinclude

TARGET = image

ELF_FILE = kernel.elf

FIRMWARE_DIR = firmware

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(ELF_FILE)
	@mkdir -p $(BUILD_DIR)/output
	$(OBJCOPY) -O binary $(BUILD_DIR)/$< $(BUILD_DIR)/output/$@
	cp $(FIRMWARE_DIR)/* $(BUILD_DIR)/output/

$(ELF_FILE): $(AS_OBJS) $(C_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) -T $(LD_SCRIPT) -o $(BUILD_DIR)/$@ $^

$(AS_OBJS): $(BUILD_DIR)/%.os: $(SRC_DIR)/%.S
	@mkdir -p $(BUILD_DIR)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) $(ASFLAG) -o $@ $<

$(C_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(INCLUDE_DIRS) -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
