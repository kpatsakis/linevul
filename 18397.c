static void fpu_init(struct sh_fpu_soft_struct *fpu)
{
	int i;

	fpu->fpscr = FPSCR_INIT;
	fpu->fpul = 0;

	for (i = 0; i < 16; i++) {
		fpu->fp_regs[i] = 0;
		fpu->xfp_regs[i]= 0;
	}
}
