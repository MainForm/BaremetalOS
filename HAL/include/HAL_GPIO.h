#ifndef __HAL_GPIO__
#define __HAL_GPIO__

#include <stdint.h>
#include <stdbool.h>

enum {
    LOW =   0,
    HIGH =  1,
};

typedef enum __GPIO_FUNC{
    GPIO_FUNC_INPUT     = 0b000, 
    GPIO_FUNC_OUTPUT    = 0b001,
    GPIO_FUNC_ALT0      = 0b100,
    GPIO_FUNC_ALT1      = 0b101, 
    GPIO_FUNC_ALT2      = 0b110, 
    GPIO_FUNC_ALT3      = 0b111, 
    GPIO_FUNC_ALT4      = 0b011, 
    GPIO_FUNC_ALT5      = 0b010, 
} GPIO_FUNC;

__attribute__((weak))
bool HAL_GPIO_IsEnable();

__attribute__((weak))
void HAL_GPIO_SetFunction(uint32_t pin, GPIO_FUNC function);

__attribute__((weak))
void HAL_GPIO_SetOutput(uint32_t pin, uint32_t value);

#endif