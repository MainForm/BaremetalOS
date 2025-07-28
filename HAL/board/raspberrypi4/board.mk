# Architecture of target board
KERNEL_ARCH			:= arm64
ARCH 				:= armv8-a
MCPU 				:= cortex-a72

TOOLCHAIN_PREFIX	:= aarch64-none-elf

# BCM2711_GPIO 	: gpio peripheral
# PL011 		: UART peripheral
# GIC-400		: interrupt peripheral
PERIPHERAL_NAMES 	:= BCM2711_GPIO BCM2711_SystemTimer PL011 GIC-400 SP804

QEMU_MACHINE_NAME 	:= raspi4b
QEMU_RAM_SIZE		:= 2G
QEMU_KERNEL			:= image