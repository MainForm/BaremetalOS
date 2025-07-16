#ifndef _BCM2711_PERIPHERAL_H
#define _BCM2711_PERIPHERAL_H

// BCM2711 GPIO register definitions
#define BCM2711_GPIO_BASE                   (0xFE200000)
#define BCM2711_GPIO_GPFSEL0                ((volatile void *)(BCM2711_GPIO_BASE + 0x00))
#define BCM2711_GPIO_GPFSEL1                ((volatile void *)(BCM2711_GPIO_BASE + 0x04))
#define BCM2711_GPIO_GPFSEL2                ((volatile void *)(BCM2711_GPIO_BASE + 0x08))
#define BCM2711_GPIO_GPFSEL3                ((volatile void *)(BCM2711_GPIO_BASE + 0x0C))
#define BCM2711_GPIO_GPFSEL4                ((volatile void *)(BCM2711_GPIO_BASE + 0x10))
#define BCM2711_GPIO_GPFSEL5                ((volatile void *)(BCM2711_GPIO_BASE + 0x14))
#define BCM2711_GPIO_GPSET0                 ((volatile void *)(BCM2711_GPIO_BASE + 0x1C))
#define BCM2711_GPIO_GPSET1                 ((volatile void *)(BCM2711_GPIO_BASE + 0x20))
#define BCM2711_GPIO_GPCLR0                 ((volatile void *)(BCM2711_GPIO_BASE + 0x28))
#define BCM2711_GPIO_GPCLR1                 ((volatile void *)(BCM2711_GPIO_BASE + 0x2C))

// BCM2711 UART0 register definitions
#define BCM2711_UART0_BASE                  (0xFE201000)
#define BCM2711_UART0_DR                    ((volatile void *)(BCM2711_UART0_BASE + 0x00))
#define BCM2711_UART0_FR                    ((volatile void *)(BCM2711_UART0_BASE + 0x18))
#define BCM2711_UART0_IBRD                  ((volatile void *)(BCM2711_UART0_BASE + 0x24))
#define BCM2711_UART0_FBRD                  ((volatile void *)(BCM2711_UART0_BASE + 0x28))
#define BCM2711_UART0_LCRH                  ((volatile void *)(BCM2711_UART0_BASE + 0x2C))
#define BCM2711_UART0_CR                    ((volatile void *)(BCM2711_UART0_BASE + 0x30))
#define BCM2711_UART0_IFLS                  ((volatile void *)(BCM2711_UART0_BASE + 0x34))
#define BCM2711_UART0_IMSC                  ((volatile void *)(BCM2711_UART0_BASE + 0x38))
#define BCM2711_UART0_MIS                   ((volatile void *)(BCM2711_UART0_BASE + 0x40))
#define BCM2711_UART0_ICR                   ((volatile void *)(BCM2711_UART0_BASE + 0x44))

#define BCM2711_ARM_LOCAL                   (0xFF800000)
#define BCM2711_CORE_IRQ_CONTROL            ((volatile void *)(BCM2711_ARM_LOCAL + 0x0C))

#define BCM2711_GIC_BASE                    (0xFF840000)

#define BCM2711_ARMC_BASE                   (0xFE00B000)
#define BCM2711_ARMC_IRQ0_SET_EN_0          ((volatile void *)(BCM2711_ARMC_BASE + 0x210))
#define BCM2711_ARMC_IRQ0_SET_EN_1          ((volatile void *)(BCM2711_ARMC_BASE + 0x214))
#define BCM2711_ARMC_IRQ0_SET_EN_2          ((volatile void *)(BCM2711_ARMC_BASE + 0x218))


#endif