#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	size_t MemoryTotal;
	size_t MemoryFree;
	size_t MemoryReserved;
	size_t MemoryBuffers;
}__attribute((packed)) MemoryInfo;

extern void (*Memcpy)(void *dest, void *src, size_t n);
extern void (*Memset)(void *start, uint8_t value, uint64_t num);
extern int (*Memcmp)(const void* buf1, const void* buf2, size_t count);

#ifdef __cplusplus
}
#endif
