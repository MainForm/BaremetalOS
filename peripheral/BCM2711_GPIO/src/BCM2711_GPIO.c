#include "BCM2711_GPIO.h"

BCM2711_GPIO* BCM2711_GPIO_GetRegisters(uintptr_t BaseAddress){
    return (BCM2711_GPIO*)BaseAddress;
}

void BCM2711_GPIO_SelectFunction(BCM2711_GPIO* gpio,uint32_t pin,FSEL_FUNC function){
    volatile uint32_t * GPSEL_base = &gpio->GPFSEL0.value;

    uint32_t regIndex = (pin / 10);
    uint32_t shiftCount = (pin % 10) * 3;

    volatile uint32_t* target_GPSEL = GPSEL_base + regIndex;

    *target_GPSEL |= (function << shiftCount);
}

void BCM2711_GPIO_SetOutput(BCM2711_GPIO* gpio,uint32_t pin,bool value){
    volatile uint32_t * Reg_base = (value == false ? &gpio->GPCLR0.value : &gpio->GPSET0.value);
    volatile uint32_t * target_Reg = Reg_base + (pin / 32);

    *target_Reg = (1 << (pin % 32));
}