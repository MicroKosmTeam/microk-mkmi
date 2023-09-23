#include <mkmi_memory.h>
#include <mkmi_syscall.h>

void *PMAlloc(size_t length) {
	void *addr;
	
	Syscall(SYSCALL_MEMORY_PMALLOC, &addr, length, 0, 0, 0, 0);
	
	return addr;
}

void *VMAlloc(uintptr_t base, size_t length, size_t flags) {
	Syscall(SYSCALL_MEMORY_VMALLOC, base, length, flags, 0, 0, 0);

	return base;
}

void *VMFree(uintptr_t base, size_t length) {
	Syscall(SYSCALL_MEMORY_VMFREE, base, length, 0, 0, 0, 0);

	return base;
}

void *VMMap(uintptr_t src, uintptr_t dest, size_t size, size_t flags) {
	Syscall(SYSCALL_MEMORY_MMAP, src, dest, size, flags, 0, 0);

	return dest;
}

void *VMUnmap(uintptr_t vaddr, size_t size) {
	Syscall(SYSCALL_MEMORY_UNMAP, vaddr, size, 0, 0, 0, 0);

	return vaddr;
}


inline void __StandardMemcpy(void *dest, void *src, size_t n) {
	char *csrc = (char *)src;
	char *cdest = (char *)dest;

	for (int i=0; i<n; i++) cdest[i] = csrc[i];
}

inline void __StandardMemset(void *start, uint8_t value, uint64_t num) {
	for (uint64_t i = 0; i < num; i++) {
		*(uint8_t*)((uint64_t)start + i) = value;
	}
}

inline int __StandardMemcmp(const void* buf1, const void* buf2, size_t count) {
	if(!count) return(0);

	while(--count && *(char*)buf1 == *(char*)buf2 ) {
		buf1 = (char*)buf1 + 1;
		buf2 = (char*)buf2 + 1;
	}

	return(*((unsigned char*)buf1) - *((unsigned char*)buf2));
}

void *Memcpy(void *dest, void *src, size_t n) {
	__StandardMemcpy(dest, src, n);

	return dest;
}

void *Memset(void *start, uint8_t value, uint64_t num) {
	__StandardMemset(start, value, num);

	return start;
}

int Memcmp(const void* buf1, const void* buf2, size_t count) {
	return __StandardMemcmp(buf1, buf2, count);
}

void *memcpy(void *dest, void *src, size_t n) {
	return Memcpy(dest, src, n);
}

void *memset(void *start, uint8_t value, uint64_t num) {
	return Memset(start, value, num);
}

int memcmp(const void* buf1, const void* buf2, size_t count) {
	return Memcmp(buf1, buf2, count);
}

size_t InPort(uintptr_t port, uint8_t size) {
	size_t result = -1;

	Syscall(SYSCALL_MEMORY_INOUT, port, false, NULL, &result, size, 0);

	return result;
}

void OutPort(uintptr_t port, size_t data, uint8_t size) {
	Syscall(SYSCALL_MEMORY_INOUT, port, true, data, NULL, size, 0);
}
