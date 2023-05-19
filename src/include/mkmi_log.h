#pragma once
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void MKMI_Printf(char *format, ...);
void MKMI_VPrintf(char *format, va_list ap);

#ifdef __cplusplus
}
#endif
