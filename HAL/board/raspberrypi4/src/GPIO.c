#include "HAL_GPIO.h"

#include "BCM2711_peripheral.h"
#include "GPIO/BCM2711_GPIO.h"

bool HAL_GPIO_IsEnable(){
    return true;
}

void HAL_GPIO_SetFunction(uint32_t pin, GPIO_FUNC function){
    BCM2711_GPIO* gpio = BCM2711_GPIO_GetRegisters(BCM2711_GPIO_BASE);

    BCM2711_GPIO_SelectFunction(gpio,pin,function);
}

void HAL_GPIO_SetOutput(uint32_t pin, uint32_t value){
    BCM2711_GPIO* gpio = BCM2711_GPIO_GetRegisters(BCM2711_GPIO_BASE);

    BCM2711_GPIO_SetOutput(gpio,pin,value);
}