#include "mkmi.h"

extern "C" void __mkmi_init() {
	mkmi_log("Hello, world, from MKMI\r\n");

}

extern "C" void __mkmi_deinit(int ret_code) {
	mkmi_log("Process exited with code: %d\r\n", ret_code);
}
