static RList* relocs(RBinFile *bf) {
	RList *ret = NULL;
	RBinReloc *ptr = NULL;
	RBinElfReloc *relocs = NULL;
	struct Elf_(r_bin_elf_obj_t) *bin = NULL;
	ut64 got_addr;
	int i;
	if (!bf || !bf->o || !bf->o->bin_obj) {
		return NULL;
	}
	bin = bf->o->bin_obj;
	if (!(ret = r_list_newf (free))) {
		return NULL;
	}
	/* FIXME: This is a _temporary_ fix/workaround to prevent a use-after-
	 * free detected by ASan that would corrupt the relocation names */
	r_list_free (imports (bf));
	if ((got_addr = Elf_(r_bin_elf_get_section_addr) (bin, ".got")) == -1) {
		got_addr = Elf_(r_bin_elf_get_section_addr) (bin, ".got.plt");
		if (got_addr == -1) {
			got_addr = 0;
		}
	}
	if (got_addr < 1 && bin->ehdr.e_type == ET_REL) {
		got_addr = Elf_(r_bin_elf_get_section_addr) (bin, ".got.r2");
		if (got_addr == -1) {
			got_addr = 0;
		}
	}
	if (bf->o) {
		if (!(relocs = Elf_(r_bin_elf_get_relocs) (bin))) {
			return ret;
		}
		for (i = 0; !relocs[i].last; i++) {
			if (!(ptr = reloc_convert (bin, &relocs[i], got_addr))) {
				continue;
			}
			r_list_append (ret, ptr);
		}
		free (relocs);
	}
	return ret;
}
