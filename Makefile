# ────────────────────────────────────────────
# 1) Tareget Board & Architecture & Toolchain
# ────────────────────────────────────────────

# Target board
TARGET_BOARD 		:= raspberrypi4

# Architecture of target board
ARCH 				:= armv8-a
MCPU 				:= cortex-a72

# Compiler for aarch64
TOOLCHAIN_PREFIX 	:= aarch64-none-elf
AS 					:= $(TOOLCHAIN_PREFIX)-as
CC 					:= $(TOOLCHAIN_PREFIX)-gcc
LD 					:= $(TOOLCHAIN_PREFIX)-gcc
OBJCOPY 			:= $(TOOLCHAIN_PREFIX)-objcopy

ASFLAG 				:= -c -g
CFLAG  				:= -c -g -Wall -O2
# This options are for the bare metal environment
LDFLAG 				:= -fno-builtin -ffreestanding -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector

# ──────────────────────────────────────────
# 2) Path & Directory
# ──────────────────────────────────────────

PROJECT_PATH 				:= $(shell pwd)
PERIPHERAL_PATH 			:= $(PROJECT_PATH)/peripheral
HAL_PATH 					:= $(PROJECT_PATH)/HAL
OS_PATH 					:= $(PROJECT_PATH)/BarementalOS
TARGET_BOARD_PATH 			:= $(HAL_PATH)/board/$(TARGET_BOARD)

# include the PERIPHERAL_NAMES variable in board.mk
# PERIPHERAL_NAMES determines which peripherals need to be built.
# BOARD_PATH might change depending on the TARGET_BOARD variable.
include $(TARGET_BOARD_PATH)/board.mk
BOARD_SRC_PATH 				:= $(TARGET_BOARD_PATH)/src
BOARD_FIRMWARE_DIR 			:= $(TARGET_BOARD_PATH)/firmware
BOARD_INCLUDE_DIR 			:= $(TARGET_BOARD_PATH)/include

PERIPHERAL_INCLUDE_DIRS  	:= $(foreach peripheral,$(PERIPHERAL_NAMES),$(shell find $(PERIPHERAL_PATH) -type d -path '*/$(peripheral)/include'))

HAL_INCLUDE_DIR 			:= $(HAL_PATH)/include

# Set the path to the BaremetalOS directory, which includes the files that need to be built.
OS_SRC_DIR 					:= $(OS_PATH)/src
OS_INCLUDE_DIR 				:= $(OS_PATH)/include

BUILD_DIR 					:= $(PROJECT_PATH)/build

# ──────────────────────────────────────────
# 3) Source files & Object files
# ──────────────────────────────────────────

PERIPHERAL_C_SRCS 	:= $(foreach peripheral,$(PERIPHERAL_NAMES),$(shell find $(PERIPHERAL_PATH) -path '*/$(peripheral)/*' -name '*.c'))
PERIPHERAL_C_OBJS 	:= $(PERIPHERAL_C_SRCS:$(PROJECT_PATH)/%.c=$(BUILD_DIR)/%.o)

BOARD_C_SRCS 		:= $(shell find $(BOARD_SRC_PATH) -name '*.c')
BOARD_C_OBJS 		:= $(BOARD_C_SRCS:$(PROJECT_PATH)/%.c=$(BUILD_DIR)/%.o)

OS_AS_SRCS 			:= $(shell find $(OS_SRC_DIR) -name '*.S')
OS_AS_OBJS 			:= $(OS_AS_SRCS:$(PROJECT_PATH)/%.S=$(BUILD_DIR)/%.os)

OS_C_SRCS 			:= $(shell find $(OS_SRC_DIR) -name '*.c')
OS_C_OBJS 			:= $(OS_C_SRCS:$(PROJECT_PATH)/%.c=$(BUILD_DIR)/%.o)

# ──────────────────────────────────────────
# 4) Linker script & Include flag
# ──────────────────────────────────────────

LD_SCRIPT 					:= $(TARGET_BOARD_PATH)/linker.ld

BOARD_INCLUDE_FLAG			:= -I$(BOARD_INCLUDE_DIR)
BOARD_INCLUDE_FLAG			+= -I$(HAL_INCLUDE_DIR)
BOARD_INCLUDE_FLAG			+= $(PERIPHERAL_INCLUDE_DIRS:%=-I%)


OS_INCLUDE_FLAG				:= -I$(HAL_INCLUDE_DIR)
OS_INCLUDE_FLAG				+= -I$(OS_INCLUDE_DIR)

# ──────────────────────────────────────────
# 5) Output file
# ──────────────────────────────────────────

TARGET 				:= image
ELF_FILE 			:= kernel.elf

# ──────────────────────────────────────────
# 6) Build rule
# ──────────────────────────────────────────
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(ELF_FILE)
	@mkdir -p $(BUILD_DIR)/output
	$(OBJCOPY) -O binary $(BUILD_DIR)/$< $(BUILD_DIR)/output/$@
	cp $(BOARD_FIRMWARE_DIR)/* $(BUILD_DIR)/output/

$(ELF_FILE): $(PERIPHERAL_C_OBJS) $(BOARD_C_OBJS) $(OS_AS_OBJS) $(OS_C_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAG) -T $(LD_SCRIPT) -o $(BUILD_DIR)/$@ $^

# Set only the include paths related to each peripheral.
# This separates the peripheral code from the BaremetalOS code.
$(PERIPHERAL_C_OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) -I$(shell dirname $(shell dirname $<))/include -o $@ $<

$(BOARD_C_OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(BOARD_INCLUDE_FLAG) -o $@ $<

$(OS_AS_OBJS): $(BUILD_DIR)/%.os: %.S
	@mkdir -p $(dir $@)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) $(ASFLAG) -o $@ $<

$(OS_C_OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(OS_INCLUDE_FLAG) -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)