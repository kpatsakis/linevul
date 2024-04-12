static void __init e820_add_kernel_range(void)
{
	u64 start = __pa_symbol(_text);
	u64 size = __pa_symbol(_end) - start;

	/*
	 * Complain if .text .data and .bss are not marked as E820_RAM and
	 * attempt to fix it by adding the range. We may have a confused BIOS,
	 * or the user may have used memmap=exactmap or memmap=xxM$yyM to
	 * exclude kernel range. If we really are running on top non-RAM,
	 * we will crash later anyways.
	 */
	if (e820_all_mapped(start, start + size, E820_RAM))
		return;

	pr_warn(".text .data .bss are not marked as E820_RAM!\n");
	e820_remove_range(start, size, E820_RAM, 0);
	e820_add_region(start, size, E820_RAM);
}
