long ia64_pal_vp_create(u64 *vpd, u64 *host_iva, u64 *opt_handler)
{
	struct ia64_pal_retval iprv;

	PAL_CALL_STK(iprv, PAL_VP_CREATE, (u64)vpd, (u64)host_iva,
			(u64)opt_handler);

	return iprv.status;
}
