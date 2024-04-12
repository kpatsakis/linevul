void emulator_invalidate_register_cache(struct x86_emulate_ctxt *ctxt)
{
	invalidate_registers(ctxt);
}
