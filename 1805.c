static int em_vmmcall(struct x86_emulate_ctxt *ctxt)
{
	int rc;

	rc = ctxt->ops->fix_hypercall(ctxt);

	/* Disable writeback. */
	ctxt->dst.type = OP_NONE;
	return rc;
}
