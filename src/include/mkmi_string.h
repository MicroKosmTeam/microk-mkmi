#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

char *strcpy(char *strDest, const char *strSrc);
int strcmp(const char *s1, const char *s2);
size_t strlen(const char *str);
void itoa(char *buf, char base, long long int num);

#ifdef __cplusplus
}
#endif
