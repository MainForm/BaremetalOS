#ifndef __BM_OS_MEMORY_H__
#define __BM_OS_MEMORY_H__

#include <stdint.h>

// Read the value from the source address only 32 bits
#define REG_32(SOURCE)           (*((volatile uint32_t*)SOURCE))

#endif