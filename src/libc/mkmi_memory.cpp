#include <mkmi_memory.h>

void __StandardMemcpy(void *dest, void *src, size_t n) {
	char *csrc = (char *)src;
	char *cdest = (char *)dest;

	for (int i=0; i<n; i++) cdest[i] = csrc[i];
}

void __StandardMemset(void *start, uint8_t value, uint64_t num) {
	for (uint64_t i = 0; i < num; i++) {
		*(uint8_t*)((uint64_t)start + i) = value;
	}
}

int __StandardMemcmp(const void* buf1, const void* buf2, size_t count) {
	if(!count) return(0);

	while(--count && *(char*)buf1 == *(char*)buf2 ) {
		buf1 = (char*)buf1 + 1;
		buf2 = (char*)buf2 + 1;
	}

	return(*((unsigned char*)buf1) - *((unsigned char*)buf2));
}

void (*Memcpy)(void *dest, void *src, size_t n) = __StandardMemcpy;
void (*Memset)(void *start, uint8_t value, uint64_t num) = __StandardMemset;
int (*Memcmp)(const void* buf1, const void* buf2, size_t count) = __StandardMemcmp;
