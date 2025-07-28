# ────────────────────────────────────────────
# 1) Tareget Board
# ────────────────────────────────────────────

# Target board
# KERNEL_ARCH, ARCH and MCPU will be set in board.mk
# supported board)
# 	- raspberrypi4
#	- realview-pb-a8
TARGET_BOARD 		:= realview-pb-a8

# ──────────────────────────────────────────
# 2) Path & Directory
# ──────────────────────────────────────────

PERIPHERAL_PATH 			:= $(PROJECT_PATH)/peripheral
HAL_PATH 					:= $(PROJECT_PATH)/HAL
OS_PATH 					:= $(PROJECT_PATH)/BaremetalOS
TARGET_BOARD_PATH 			:= $(HAL_PATH)/board/$(TARGET_BOARD)

include $(TARGET_BOARD_PATH)/board.mk

TOP_BUILD_DIR 				:= $(PROJECT_PATH)/build
TARGET_BOARD_BUILD_DIR 		:= $(TOP_BUILD_DIR)/$(TARGET_BOARD)

# ──────────────────────────────────────────
# 3) Toolchain & Flags
# ──────────────────────────────────────────

# TOOLCHAIN_PREFIX is set in board.mk
AS 					:= $(TOOLCHAIN_PREFIX)-as
CC 					:= $(TOOLCHAIN_PREFIX)-gcc
LD 					:= $(TOOLCHAIN_PREFIX)-gcc
OBJCOPY 			:= $(TOOLCHAIN_PREFIX)-objcopy
GDB					:= $(TOOLCHAIN_PREFIX)-gdb

ASFLAG 				:= -c -g $(BOARD_AS_FLAG)
CFLAG  				:= -c -g -Wall -O2