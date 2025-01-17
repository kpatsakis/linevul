char* Elf_(r_bin_elf_get_arch)(ELFOBJ *bin) {
	switch (bin->ehdr.e_machine) {
	case EM_ARC:
	case EM_ARC_A5:
		return strdup ("arc");
	case EM_AVR: return strdup ("avr");
	case EM_CRIS: return strdup ("cris");
	case EM_68K: return strdup ("m68k");
	case EM_MIPS:
	case EM_MIPS_RS3_LE:
	case EM_MIPS_X:
		return strdup ("mips");
	case EM_MCST_ELBRUS:
		return strdup ("elbrus");
	case EM_TRICORE:
		return strdup ("tricore");
	case EM_ARM:
	case EM_AARCH64:
		return strdup ("arm");
	case EM_HEXAGON:
		return strdup ("hexagon");
	case EM_BLACKFIN:
		return strdup ("blackfin");
	case EM_SPARC:
	case EM_SPARC32PLUS:
	case EM_SPARCV9:
		return strdup ("sparc");
	case EM_PPC:
	case EM_PPC64:
		return strdup ("ppc");
	case EM_PARISC:
		return strdup ("hppa");
	case EM_PROPELLER:
		return strdup ("propeller");
	case EM_MICROBLAZE:
		return strdup ("microblaze.gnu");
	case EM_RISCV:
		return strdup ("riscv");
	case EM_VAX:
		return strdup ("vax");
	case EM_XTENSA:
		return strdup ("xtensa");
	case EM_LANAI:
		return strdup ("lanai");
	case EM_VIDEOCORE3:
	case EM_VIDEOCORE4:
		return strdup ("vc4");
	case EM_SH:
		return strdup ("sh");
	case EM_V850:
		return strdup ("v850");
	case EM_IA_64:
		return strdup("ia64");
	default: return strdup ("x86");
	}
}
