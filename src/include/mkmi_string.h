#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

bool IsDelim(char c, char *delim);

char *Strcpy(char *strDest, const char *strSrc);
int Strcmp(const char *s1, const char *s2);
size_t Strlen(const char *str);
char *Strtok(char *s, char *delim);

void Itoa(char *buf, char base, long long int num);
intmax_t Atoi(char *str);

#ifdef __cplusplus
}
#endif
