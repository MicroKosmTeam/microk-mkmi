extern "C" void __mkmi_init() {

}

extern "C" void __mkmi_deinit() {

	__builtin_trap();
	__builtin_unreachable();
}
