#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char *str);
void itoa(char *buf, char base, long long int num);

#ifdef __cplusplus
}
#endif
