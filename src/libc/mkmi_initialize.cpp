#include "mkmi.h"

extern "C" void __mkmi_init(usize vregsSize, usize *vregs) {
	__MKMI_InitArgs(vregs, vregsSize);
	MKMI_Log("VRegs:    0x%x\r\n"
		 "VRegs size: %d\r\n", vregs, vregsSize);
}

extern "C" void __mkmi_deinit(int retCode) {

}
