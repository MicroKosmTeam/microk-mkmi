extern "C" int Main(void *parent);

extern "C" void __mkmi_init() {
}

extern "C" void __mkmi_deinit() {
	/* Wait for time to consume us */
	for (;;);
		
	__builtin_unreachable();
}
