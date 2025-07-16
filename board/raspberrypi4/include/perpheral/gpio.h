#ifndef __BCM2711_GPIO_H__
#define __BCM2711_GPIO_H__

#include <stdint.h>
#include <stdbool.h>

#define GPIO_FUNC_INPUT     (0x00)
#define GPIO_FUNC_OUTPUT    (0x01)
#define GPIO_FUNC_ALT0      (0x04)
#define GPIO_FUNC_ALT1      (0x05)
#define GPIO_FUNC_ALT2      (0x06)
#define GPIO_FUNC_ALT3      (0x07)
#define GPIO_FUNC_ALT4      (0x03)
#define GPIO_FUNC_ALT5      (0x02)

void GPIO_SelectFunction(uint32_t pin, uint32_t function);
void GPIO_SetOutput(uint32_t pin,bool value);

#endif