#ifndef __BM_OS_MEMORY_H__
#define __BM_OS_MEMORY_H__

#include <stdint.h>

// Write the value to the destination(DEST) address only 32 bits
#define WRITE_MEMROY_32(DEST, VALUE)    (*((volatile uint32_t*)DEST) = (uint32_t)VALUE)

// Read the value from the source address only 32 bits
#define READ_MEMRY_32(SOURCE)           ((uint32_t)(*(volatile uint32_t*)(SOURCE)))

#endif