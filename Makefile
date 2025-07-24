

# ────────────────────────────────────────────
# 1) Tareget Board
# ────────────────────────────────────────────

# Target board
# KERNEL_ARCH, ARCH and MCPU will be set in board.mk
TARGET_BOARD 		:= realview-pb-a8

# ──────────────────────────────────────────
# 2) Path & Directory
# ──────────────────────────────────────────

PROJECT_PATH 				:= .
PERIPHERAL_PATH 			:= $(PROJECT_PATH)/peripheral
HAL_PATH 					:= $(PROJECT_PATH)/HAL
OS_PATH 					:= $(PROJECT_PATH)/BarementalOS
TARGET_BOARD_PATH 			:= $(HAL_PATH)/board/$(TARGET_BOARD)

include $(TARGET_BOARD_PATH)/board.mk

# include the PERIPHERAL_NAMES variable in board.mk
# PERIPHERAL_NAMES determines which peripherals need to be built.
# BOARD_PATH might change depending on the TARGET_BOARD variable.
BOARD_SRC_PATH 				:= $(TARGET_BOARD_PATH)/src
BOARD_FIRMWARE_DIR 			:= $(TARGET_BOARD_PATH)/firmware
BOARD_INCLUDE_DIR 			:= $(TARGET_BOARD_PATH)/include

PERIPHERAL_INCLUDE_DIRS  	:= $(foreach peripheral,$(PERIPHERAL_NAMES),$(shell find $(PERIPHERAL_PATH) -type d -path '*/$(peripheral)/include'))

HAL_INCLUDE_DIR 			:= $(HAL_PATH)/include

# Set the path to the BaremetalOS directory, which includes the files that need to be built.
OS_SRC_DIR 					:= $(OS_PATH)/src
OS_ARCH_SRC_DIR				:= $(OS_SRC_DIR)/arch/$(KERNEL_ARCH)
OS_KERNEL_SRC_DIR			:= $(OS_SRC_DIR)/kernel
OS_INCLUDE_DIR 				:= $(OS_PATH)/include

BUILD_DIR 					:= $(PROJECT_PATH)/build


# ──────────────────────────────────────────
# 3) Architecture & Toolchain
# ──────────────────────────────────────────

# Compiler for aarch64
AS 					:= $(TOOLCHAIN_PREFIX)-as
CC 					:= $(TOOLCHAIN_PREFIX)-gcc
LD 					:= $(TOOLCHAIN_PREFIX)-gcc
OBJCOPY 			:= $(TOOLCHAIN_PREFIX)-objcopy
GDB					:= $(TOOLCHAIN_PREFIX)-gdb

ASFLAG 				:= -c -g $(BOARD_AS_FLAG)
CFLAG  				:= -c -g -Wall -O2
# This options are for the bare metal environment
LDFLAG 				:= -fno-builtin -ffreestanding -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector

LIB_FLAG			:= -lgcc

# this variable is for GDB
GDB_REMOTE_PORT		:= 9874

# This variable is for the qemu emulation
# QEMU_MACHINE_NAME and QEMU_RAM_SIZE will be set in board.mk, which is located in TARGET_BOARD_PATH
QEMU				:= qemu-system-aarch64
QEMU_FLAG 			:= -nographic
QEMU_DEBUG_FLAG		:= -S -gdb tcp::$(GDB_REMOTE_PORT),ipv4

# ──────────────────────────────────────────
# 4) Source files & Object files
# ──────────────────────────────────────────

PERIPHERAL_C_SRCS 	:= $(foreach peripheral,$(PERIPHERAL_NAMES),$(shell find $(PERIPHERAL_PATH) -path '*/$(peripheral)/*' -name '*.c'))
PERIPHERAL_C_OBJS 	:= $(PERIPHERAL_C_SRCS:$(PROJECT_PATH)/%.c=$(BUILD_DIR)/%.o)

BOARD_C_SRCS 		:= $(shell find $(BOARD_SRC_PATH) -name '*.c')
BOARD_C_OBJS 		:= $(BOARD_C_SRCS:$(PROJECT_PATH)/%.c=$(BUILD_DIR)/%.o)

OS_ARCH_AS_SRCS 	:= $(shell find $(OS_ARCH_SRC_DIR) -name '*.S')
OS_ARCH_AS_OBJS 	:= $(OS_ARCH_AS_SRCS:$(PROJECT_PATH)/%.S=$(BUILD_DIR)/%.os)

OS_ARCH_C_SRCS 	:= $(shell find $(OS_ARCH_SRC_DIR) -name '*.c')
OS_ARCH_C_OBJS 	:= $(OS_ARCH_C_SRCS:$(PROJECT_PATH)/%.c=$(BUILD_DIR)/%.o)

OS_KERNEL_C_SRCS 	:= $(shell find $(OS_KERNEL_SRC_DIR) -name '*.c')
OS_KERNEL_C_OBJS 	:= $(OS_KERNEL_C_SRCS:$(PROJECT_PATH)/%.c=$(BUILD_DIR)/%.o)

# ──────────────────────────────────────────
# 5) Linker script & Include flag
# ──────────────────────────────────────────

LD_SCRIPT 					:= $(TARGET_BOARD_PATH)/linker.ld

BOARD_INCLUDE_FLAG			:= -I$(BOARD_INCLUDE_DIR)
BOARD_INCLUDE_FLAG			+= -I$(HAL_INCLUDE_DIR)
BOARD_INCLUDE_FLAG			+= $(PERIPHERAL_INCLUDE_DIRS:%=-I%)

OS_INCLUDE_FLAG				:= -I$(HAL_INCLUDE_DIR)
OS_INCLUDE_FLAG				+= -I$(OS_INCLUDE_DIR)

# ──────────────────────────────────────────
# 6) Output file
# ──────────────────────────────────────────

TARGET 				:= image
ELF_FILE 			:= kernel.elf

# ──────────────────────────────────────────
# 7) Build rule
# ──────────────────────────────────────────
.PHONY: all clean qemu_run qemu_debug gdb

all: $(TARGET)

$(TARGET): $(ELF_FILE)
	@mkdir -p $(BUILD_DIR)/output
	$(OBJCOPY) -O binary $(BUILD_DIR)/$< $(BUILD_DIR)/$@

$(ELF_FILE): $(PERIPHERAL_C_OBJS) $(BOARD_C_OBJS) $(OS_ARCH_AS_OBJS) $(OS_ARCH_C_OBJS) $(OS_KERNEL_C_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAG) -T $(LD_SCRIPT) -o $(BUILD_DIR)/$@ $^ $(LIB_FLAG)

# Set only the include paths related to each peripheral.
# This separates the peripheral code from the BaremetalOS code.
$(PERIPHERAL_C_OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) -I$(shell dirname $(shell dirname $<))/include -o $@ $<

$(BOARD_C_OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(BOARD_INCLUDE_FLAG) -o $@ $<

$(OS_ARCH_AS_OBJS): $(BUILD_DIR)/%.os: %.S
	@mkdir -p $(dir $@)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) $(ASFLAG) -o $@ $<

$(OS_ARCH_C_OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(OS_INCLUDE_FLAG) -o $@ $<

$(OS_KERNEL_C_OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) $(OS_INCLUDE_FLAG) -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)

qemu_run: $(TARGET)
	$(QEMU) -M $(QEMU_MACHINE_NAME) -m $(QEMU_RAM_SIZE) -kernel $(BUILD_DIR)/$(TARGET) $(QEMU_FLAG)

qemu_debug: $(TARGET)
	$(QEMU) -M $(QEMU_MACHINE_NAME) -kernel $(BUILD_DIR)/$(QEMU_KERNEL) $(QEMU_FLAG) $(QEMU_DEBUG_FLAG)

gdb:
	$(GDB) 	-ex "file $(BUILD_DIR)/$(ELF_FILE)" 				\
			-ex "target remote localhost:$(GDB_REMOTE_PORT)"	\
			-ex "layout regs"									\
			-ex "break _start"