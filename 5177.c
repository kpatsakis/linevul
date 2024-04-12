void __user *insn_get_addr_ref(struct insn *insn, struct pt_regs *regs)
{
	if (!insn || !regs)
		return (void __user *)-1L;

	switch (insn->addr_bytes) {
	case 2:
		return get_addr_ref_16(insn, regs);
	case 4:
		return get_addr_ref_32(insn, regs);
	case 8:
		return get_addr_ref_64(insn, regs);
	default:
		return (void __user *)-1L;
	}
}
