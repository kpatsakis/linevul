static void store_reg(struct pt_regs *regs, unsigned long val, unsigned long rd)
{
	if (rd < 16) {
		unsigned long *rd_kern = __fetch_reg_addr_kern(rd, regs);

		*rd_kern = val;
	} else {
		unsigned long __user *rd_user = __fetch_reg_addr_user(rd, regs);

		if (test_thread_flag(TIF_32BIT))
			__put_user((u32)val, (u32 __user *)rd_user);
		else
			__put_user(val, rd_user);
	}
}
