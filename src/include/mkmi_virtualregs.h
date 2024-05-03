#pragma once
#include <cdefs.h>

#include <stdarg.h>

#ifdef __cplusplus__
extern "C" {
#endif 

void __mkmi_init_args(usize *args, usize args_size);
void __mkmi_set_args(usize total_args, va_list ap);
usize __mkmi_get_arg_index(usize index);
void __mkmi_clear_args();

#ifdef __cplusplus__
}
#endif 

