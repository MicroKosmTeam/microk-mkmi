#pragma once
#include <cdefs.h>

#include <stdarg.h>

#ifdef __cplusplus__
extern "C" {
#endif 

void __MKMI_InitArgs(usize *args, usize argsSize);
void __MKMI_SetArgs(usize totalArgs, va_list ap);
usize __MKMI_GetArgIndex(usize index);
void __MKMI_ClearArgs();

#ifdef __cplusplus__
}
#endif 

