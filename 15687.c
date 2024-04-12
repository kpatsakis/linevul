static int __do_insn_fetch_bytes(struct x86_emulate_ctxt *ctxt, int op_size)
{
	int rc;
	unsigned size;
	unsigned long linear;
	int cur_size = ctxt->fetch.end - ctxt->fetch.data;
	struct segmented_address addr = { .seg = VCPU_SREG_CS,
					   .ea = ctxt->eip + cur_size };

	size = 15UL ^ cur_size;
	rc = __linearize(ctxt, addr, size, false, true, &linear);
	if (unlikely(rc != X86EMUL_CONTINUE))
		return rc;

	size = min_t(unsigned, size, PAGE_SIZE - offset_in_page(linear));

	/*
	 * One instruction can only straddle two pages,
	 * and one has been loaded at the beginning of
	 * x86_decode_insn.  So, if not enough bytes
	 * still, we must have hit the 15-byte boundary.
	 */
	if (unlikely(size < op_size))
		return X86EMUL_UNHANDLEABLE;
	rc = ctxt->ops->fetch(ctxt, linear, ctxt->fetch.end,
			      size, &ctxt->exception);
	if (unlikely(rc != X86EMUL_CONTINUE))
		return rc;
	ctxt->fetch.end += size;
	return X86EMUL_CONTINUE;
}
