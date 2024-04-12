static void add_metadata(RCore *r, RBinReloc *reloc, ut64 addr, int mode) {
	RBinFile * binfile = r->bin->cur;
	RBinObject *binobj = binfile ? binfile->o: NULL;
	RBinInfo *info = binobj ? binobj->info: NULL;
	RIOSection *section;
	int cdsz;

	cdsz = info? (info->bits == 64? 8: info->bits == 32? 4: info->bits == 16 ? 4: 0): 0;
	if (cdsz == 0) {
		return;
	}

	section = r_io_section_vget (r->io, addr);
	if (!section || section->flags & R_IO_EXEC) {
		return;
	}

	if (IS_MODE_SET(mode)) {
		r_meta_add (r->anal, R_META_TYPE_DATA, reloc->vaddr, reloc->vaddr + cdsz, NULL);
	} else if (IS_MODE_RAD (mode)) {
		r_cons_printf ("f Cd %d @ 0x%08" PFMT64x "\n", cdsz, addr);
	}
}
