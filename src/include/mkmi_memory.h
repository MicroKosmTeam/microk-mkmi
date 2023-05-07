#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void (*Memcpy)(void *dest, void *src, size_t n);
extern void (*Memset)(void *start, uint8_t value, uint64_t num);
extern int (*Memcmp)(const void* buf1, const void* buf2, size_t count);

#ifdef __cplusplus
}
#endif
