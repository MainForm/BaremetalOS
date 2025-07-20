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

PROJECT_PATH = $(shell pwd)

OS_PATH = $(PROJECT_PATH)/BarementalOS
OS_SRC_DIR = $(OS_PATH)/src
OS_INCLUDE_DIR = $(OS_PATH)/include

BOARD_PATH = $(PROJECT_PATH)/board/$(TARGET_BOARD)
BOARD_FIRMWARE_DIR = $(BOARD_PATH)/firmware
include $(BOARD_PATH)/board.mk
#BOARD_SRC_DIR = $(BOARD_PATH)/src

INCLUDE_DIRS = $(shell find . -type d -path '*/include')
INCLUD_FLAG = $(foreach inc_dir,$(INCLUDE_DIRS),-I$(inc_dir))

BUILD_DIR = build

OS_AS_SRCS = $(shell find $(OS_SRC_DIR) -name '*.S')
OS_AS_OBJS = $(OS_AS_SRCS:$(OS_SRC_DIR)/%.S=$(BUILD_DIR)/%.os)

OS_C_SRCS = $(shell find $(OS_SRC_DIR) -name '*.c')
OS_C_OBJS = $(OS_C_SRCS:$(OS_SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

PERIPHERAL_C_SRCS = $(foreach peripheral,$(PERIPHERAL_NAMES),$(shell find $(PERIPHERAL_PATH) -path '*/$(peripheral)/*' -name '*.c'))
PERIPHERAL_C_OBJS = $(PERIPHERAL_C_SRCS:$(shell pwd)/%.c=$(BUILD_DIR)/%.o) 

# BOARD_C_SRCS = $(shell find $(BOARD_SRC_DIR) -name '*.c')
# BOARD_C_OBJS = $(BOARD_C_SRCS:$(BOARD_SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LD_SCRIPT = linker.ld

TARGET = image
ELF_FILE = kernel.elf

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(ELF_FILE)
	@mkdir -p $(BUILD_DIR)/output
	$(OBJCOPY) -O binary $(BUILD_DIR)/$< $(BUILD_DIR)/output/$@
	cp $(BOARD_FIRMWARE_DIR)/* $(BUILD_DIR)/output/

$(ELF_FILE): $(OS_AS_OBJS) $(OS_C_OBJS) $(PERIPHERAL_C_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAG) -T $(LD_SCRIPT) -o $(BUILD_DIR)/$@ $^

$(OS_AS_OBJS): $(BUILD_DIR)/%.os: $(OS_SRC_DIR)/%.S
	@mkdir -p $(BUILD_DIR)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) $(ASFLAG) -o $@ $<

$(OS_C_OBJS): $(BUILD_DIR)/%.o: $(OS_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(INCLUD_FLAG) -o $@ $<

$(PERIPHERAL_C_OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(INCLUD_FLAG) -o $@ $<

test:
	echo "$(PROJECT_PATH)"

clean:
	@rm -rf $(BUILD_DIR)
