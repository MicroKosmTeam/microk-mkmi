#include "mkmi.h"

extern "C" void __mkmi_init(usize vregsSize, u8 *vregs) {
	MKMI_Log("VRegs:    0x%x\r\n"
		 "VRegs size: %d\r\n", vregs, vregsSize);
	MKMI_InitArgs(vregs, vregsSize);
}

extern "C" void __mkmi_deinit(int retCode) {

}
