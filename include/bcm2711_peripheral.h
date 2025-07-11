#ifndef _BCM2711_PERIPHERAL_H
#define _BCM2711_PERIPHERAL_H

// BCM2711 GPIO register definitions
#define BCM2711_GPIO_BASE   (0xFE200000)
#define BCM2711_GPFSE1      ((volatile void *)(BCM2711_GPIO_BASE + 0x04))
#define BCM2711_GPFSE2      ((volatile void *)(BCM2711_GPIO_BASE + 0x08))
#define BCM2711_GPSET0      ((volatile void *)(BCM2711_GPIO_BASE + 0x1C))
#define BCM2711_GPCLR0      ((volatile void *)(BCM2711_GPIO_BASE + 0x28))

// BCM2711 UART0 register definitions

#define BCM2711_UART0_BASE  (0xFE201000)
#define BCM2711_UART0_DR    ((volatile void *)(BCM2711_UART0_BASE + 0x00))
#define BCM2711_UART0_FR    ((volatile void *)(BCM2711_UART0_BASE + 0x18))
#define BCM2711_UART0_IBRD  ((volatile void *)(BCM2711_UART0_BASE + 0x24))
#define BCM2711_UART0_FBRD  ((volatile void *)(BCM2711_UART0_BASE + 0x28))
#define BCM2711_UART0_LCRH  ((volatile void *)(BCM2711_UART0_BASE + 0x2C))
#define BCM2711_UART0_CR    ((volatile void *)(BCM2711_UART0_BASE + 0x30))
#define BCM2711_UART0_IFLS  ((volatile void *)(BCM2711_UART0_BASE + 0x34))

#endif