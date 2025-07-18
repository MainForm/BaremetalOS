#ifndef _BCM2711_PERIPHERAL_H
#define _BCM2711_PERIPHERAL_H



#define BCM2711_GIC_BASE                    (0xFF840000)

#define BCM2711_ARMC_BASE                   (0xFE00B000)
#define BCM2711_ARMC_IRQ0_SET_EN_0          ((volatile void *)(BCM2711_ARMC_BASE + 0x210))
#define BCM2711_ARMC_IRQ0_SET_EN_1          ((volatile void *)(BCM2711_ARMC_BASE + 0x214))
#define BCM2711_ARMC_IRQ0_SET_EN_2          ((volatile void *)(BCM2711_ARMC_BASE + 0x218))

#endif