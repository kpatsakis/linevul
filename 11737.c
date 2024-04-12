SYSCALL_DEFINE1(osf_brk, unsigned long, brk)
{
	unsigned long retval = sys_brk(brk);
	if (brk && brk != retval)
		retval = -ENOMEM;
	return retval;
}
