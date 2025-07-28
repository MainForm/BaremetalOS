# ───────────────────────────────────────────────────────────
# 1) Set the top of project path
# ───────────────────────────────────────────────────────────

PROJECT_PATH 	:= $(shell pwd)
export PROJECT_PATH

# ───────────────────────────────────────────────────────────
# 2) Include in common.mk to set up the shared variables
# ───────────────────────────────────────────────────────────

include common.mk

# ───────────────────────────────────────────────────────────
# 3) Set the path of Linker script
# ───────────────────────────────────────────────────────────

LD_SCRIPT 			:= $(TARGET_BOARD_PATH)/linker.ld

# ───────────────────────────────────────────────────────────
# 4) Set the name of output file
# ───────────────────────────────────────────────────────────

TARGET 				:= image
ELF_FILE 			:= kernel.elf

# ───────────────────────────────────────────────────────────
# 5) Linker options
# ───────────────────────────────────────────────────────────

# This options are for the bare metal environment
LDFLAG 				:= -fno-builtin -ffreestanding -nostartfiles -nostdlib -nodefaultlibs -static -fno-stack-protector
LIB_FLAG			:= -lgcc

# ───────────────────────────────────────────────────────────
# 5) Qemu configuration
# ───────────────────────────────────────────────────────────

# this variable is for GDB
GDB_REMOTE_PORT		:= 9874

# This variable is for the qemu emulation
# QEMU_MACHINE_NAME and QEMU_RAM_SIZE will be set in board.mk, which is located in TARGET_BOARD_PATH
QEMU				:= qemu-system-aarch64
QEMU_FLAG 			:= -nographic
QEMU_DEBUG_FLAG		:= -S -gdb tcp::$(GDB_REMOTE_PORT),ipv4

# ───────────────────────────────────────────────────────────
# 6) Build rules
# ───────────────────────────────────────────────────────────

.PHONY: all clean qemu_run qemu_debug gdb

all: $(TARGET)

$(TARGET): $(ELF_FILE)
	$(OBJCOPY) -O binary $(TARGET_BOARD_BUILD_DIR)/$< $(TARGET_BOARD_BUILD_DIR)/$@

$(ELF_FILE):
	@mkdir -p $(TARGET_BOARD_BUILD_DIR)

	$(MAKE) -C $(PERIPHERAL_PATH)
	$(MAKE) -C $(HAL_PATH)
	$(MAKE) -C $(OS_PATH)

	$(LD) $(LDFLAG) -T $(LD_SCRIPT) -o $(TARGET_BOARD_BUILD_DIR)/$@ $$(find $(TARGET_BOARD_BUILD_DIR) -name '*.o' -o -name '*.os') $(LIB_FLAG)

clean:
	@rm -rf $(TOP_BUILD_DIR)

qemu_run: $(TARGET)
	$(QEMU) -M $(QEMU_MACHINE_NAME) -m $(QEMU_RAM_SIZE) -kernel $(TARGET_BOARD_BUILD_DIR)/$(QEMU_KERNEL) $(QEMU_FLAG)

qemu_debug: $(TARGET)
	$(QEMU) -M $(QEMU_MACHINE_NAME) -m $(QEMU_RAM_SIZE) -kernel $(TARGET_BOARD_BUILD_DIR)/$(QEMU_KERNEL) $(QEMU_FLAG) $(QEMU_DEBUG_FLAG)

gdb:
	$(GDB) 	-ex "file $(TARGET_BOARD_BUILD_DIR)/$(ELF_FILE)" 	\
			-ex "target remote localhost:$(GDB_REMOTE_PORT)"	\
			-ex "layout regs"									\
			-ex "break _start"