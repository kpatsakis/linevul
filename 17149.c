static int em_sidt(struct x86_emulate_ctxt *ctxt)
{
	return emulate_store_desc_ptr(ctxt, ctxt->ops->get_idt);
}
