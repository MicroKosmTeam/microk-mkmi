#pragma once
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus__
extern "C" {
#endif

void *memcpy(void *dst0, const void *src0, size_t length);
void *memset(void *dst0, int c0, size_t length);
void *memmove(void *s1, const void *s2, size_t n);
int memcmp(const void *ptr1, const void *ptr2, size_t count);

char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
size_t strlen(const char *str);

#ifdef __cplusplus__
}
#endif
