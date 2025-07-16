#include "bcm2711_peripheral.h"
#include "perpheral/gpio.h"

#include "memory.h"

void GPIO_SelectFunction(uint32_t pin, uint32_t function){
    volatile uint32_t * GPSEL_base = BCM2711_GPIO_GPFSEL0;

    uint32_t regIndex = (pin / 10);
    uint32_t shiftCount = (pin % 10) * 3;

    REG_32(GPSEL_base + regIndex) |= ((function & 0x07) << shiftCount);
}

void GPIO_SetOutput(uint32_t pin,bool value){
    volatile uint32_t * Reg = (value == false ? BCM2711_GPIO_GPCLR0 : BCM2711_GPIO_GPSET0);

    REG_32(Reg + (pin / 32)) = (1 << (pin % 32));
}