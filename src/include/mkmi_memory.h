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

void *PMAlloc(size_t length);

void *VMAlloc(uintptr_t base, size_t length, size_t flags);
void *VMFree(uintptr_t base, size_t length);

void *VMMap(uintptr_t src, uintptr_t dest, size_t size, size_t flags);
void *VMUnmap(uintptr_t vaddr, size_t size);

void *Malloc(size_t size);
void *Free(void *address);

size_t InPort(uintptr_t port, uint8_t size);
void OutPort(uintptr_t port, size_t data, uint8_t size);

inline void *operator new(size_t size) {
	return Malloc(size);
}

inline void *operator new[](size_t size) {
	return Malloc(size);
}

inline void operator delete(void* p) {
	Free(p);
}

inline void operator delete[](void* p) {
	Free(p);
}

inline void operator delete(void* p, size_t unused) {
	Free(p);
}

inline void operator delete[](void* p, size_t unused) {
	Free(p);
}

void *Memcpy(void *dest, void *src, size_t n);
void *Memset(void *start, uint8_t value, uint64_t num);
int Memcmp(const void* buf1, const void* buf2, size_t count);

/* The compiler might indiscriminately call those functions,
 * expecting their original names. This fixes the issue. */
void *memcpy(void *dest, void *src, size_t n);
void *memset(void *start, uint8_t value, uint64_t num);
int memcmp(const void* buf1, const void* buf2, size_t count);

#ifdef __cplusplus
}
#endif
