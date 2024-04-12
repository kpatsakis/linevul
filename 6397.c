fmov_reg_idx(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m,
	     int n)
{
	if (FPSCR_SZ) {
		FMOV_EXT(m);
		WRITE(FRm, Rn + R0 + 4);
		m++;
		WRITE(FRm, Rn + R0);
	} else {
		WRITE(FRm, Rn + R0);
	}

	return 0;
}
