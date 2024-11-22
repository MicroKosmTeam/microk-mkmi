PHDRS
{
	text	PT_LOAD	FLAGS((1 << 0) | (1 << 2));	/* Execute + Read */
	rodata	PT_LOAD	FLAGS((1 << 2));		/* Read only */
	data	PT_LOAD	FLAGS((1 << 1) | (1 << 2));	/* Write + Read */
}

SECTIONS
{
	.text : {
		*(.text .text.*)
	} :text

	.rodata : {
		*(.rodata .rodata.*)
	} :rodata

	.data : {
		*(.data .data.*)
	} :data

	.bss : {
		*(COMMON)
		*(.bss .bss.*)
	} :data

	/DISCARD/ : {
		*(.eh_frame)
		*(.note .note.*)
	}
}
