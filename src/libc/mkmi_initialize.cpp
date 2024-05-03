#include "mkmi.h"

extern "C" void __mkmi_init(usize vregs_size, usize *vregs) {
	__mkmi_init_args(vregs, vregs_size);

	mkmi_log("VRegs:    0x%x\r\n"
		 "VRegs size: %d\r\n", vregs, vregs_size);
}

extern "C" void __mkmi_deinit(int ret_code) {

}
