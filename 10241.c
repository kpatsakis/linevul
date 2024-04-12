static void get_descriptor_table_ptr(struct x86_emulate_ctxt *ctxt,
				     u16 selector, struct desc_ptr *dt)
{
	const struct x86_emulate_ops *ops = ctxt->ops;
	u32 base3 = 0;

	if (selector & 1 << 2) {
		struct desc_struct desc;
		u16 sel;

		memset (dt, 0, sizeof *dt);
		if (!ops->get_segment(ctxt, &sel, &desc, &base3,
				      VCPU_SREG_LDTR))
			return;

		dt->size = desc_limit_scaled(&desc); /* what if limit > 65535? */
		dt->address = get_desc_base(&desc) | ((u64)base3 << 32);
	} else
		ops->get_gdt(ctxt, dt);
}
