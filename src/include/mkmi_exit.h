#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void _exit(size_t exitCode);
void _return(size_t returnCode);

#ifdef __cplusplus
}
#endif
