#pragma once
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void mkmi_assert(bool expression, char *file, char *function, size_t line);
#define ASSERT(expression) mkmi_assert( expression, __FILE__, __FUNCTION__, __LINE__ ), __builtin_unreachable()


#ifdef __cplusplus
}
#endif
