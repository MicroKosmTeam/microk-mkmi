#pragma once
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void *dst0, const void *src0, size_t length);
void *memset(void *dst0, int c0, size_t length);
void *memmove(void *s1, const void *s2, size_t n);
int memcmp(const void *ptr1, const void *ptr2, size_t count);

bool is_delim(char c, char *delim);

char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
size_t strlen(const char *str);
size_t strcspn(const char *s1, const char *s2);
size_t strspn(const char *s1, const char *s2);
char *strtok(char *string, const char *delim, char **savePtr);

#ifdef __cplusplus
}
#endif
