static int flush_pending_x87_faults(struct x86_emulate_ctxt *ctxt)
{
	bool fault = false;

	ctxt->ops->get_fpu(ctxt);
	asm volatile("1: fwait \n\t"
		     "2: \n\t"
		     ".pushsection .fixup,\"ax\" \n\t"
		     "3: \n\t"
		     "movb $1, %[fault] \n\t"
		     "jmp 2b \n\t"
		     ".popsection \n\t"
		     _ASM_EXTABLE(1b, 3b)
		     : [fault]"+qm"(fault));
	ctxt->ops->put_fpu(ctxt);

	if (unlikely(fault))
		return emulate_exception(ctxt, MF_VECTOR, 0, false);

	return X86EMUL_CONTINUE;
}
