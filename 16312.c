static int fcnvds(struct sh_fpu_soft_struct *fregs, int n)
{
	FP_DECL_EX;
	FP_DECL_D(Fn);
	FP_DECL_S(Fr);
	UNPACK_D(Fn, DRn);
	FP_CONV(S, D, 1, 2, Fr, Fn);
	PACK_S(FPUL, Fr);
	return 0;
}
