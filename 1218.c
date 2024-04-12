char* MACH0_(get_cpusubtype)(struct MACH0_(obj_t)* bin) {
	if (bin) {
		return MACH0_(get_cpusubtype_from_hdr) (&bin->hdr);
	}
	return strdup ("Unknown");
}
