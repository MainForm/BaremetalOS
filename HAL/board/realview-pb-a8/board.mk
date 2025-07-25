# Architecture of target board
KERNEL_ARCH			:= arm
ARCH 				:= armv7-a
MCPU 				:= cortex-a8

# Notify the compiler that the FPU is enabled.
# This flag makes the instruction `VMSR FPEXC, R0` valid.
BOARD_AS_FLAG		:= -mfpu=vfpv3-d16

TOOLCHAIN_PREFIX	:= arm-none-eabi

# PL011 		: UART peripheral
# PB-A8_GIC		: interrupt peripheral
# SP804			: dual-mode timer peripheral
PERIPHERAL_NAMES 	:= PL011 PB-A8_GIC SP804

QEMU_MACHINE_NAME 	:= realview-pb-a8
QEMU_RAM_SIZE		:= 512M
QEMU_KERNEL			:= kernel.elf