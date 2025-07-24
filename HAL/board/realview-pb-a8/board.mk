# Architecture of target board
KERNEL_ARCH			:= arm
ARCH 				:= armv7-a
MCPU 				:= cortex-a8

# Notify the compiler that the FPU is enabled.
# This flag makes the instruction `VMSR FPEXC, R0` valid.
BOARD_AS_FLAG		:= -mfpu=vfpv3-d16

TOOLCHAIN_PREFIX	:= arm-none-eabi

# PL011 		: UART peripheral
# GIC-400		: interrupt peripheral
PERIPHERAL_NAMES 	:=

QEMU_MACHINE_NAME 	:= realview-pb-a8
QEMU_RAM_SIZE		:= 2G
QEMU_KERNEL			:= kernel.elf