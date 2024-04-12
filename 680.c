static int do_proc_dointvec_ms_jiffies_conv(bool *negp, unsigned long *lvalp,
					    int *valp,
					    int write, void *data)
{
	if (write) {
		unsigned long jif = msecs_to_jiffies(*negp ? -*lvalp : *lvalp);

		if (jif > INT_MAX)
			return 1;
		*valp = (int)jif;
	} else {
		int val = *valp;
		unsigned long lval;
		if (val < 0) {
			*negp = true;
			lval = -(unsigned long)val;
		} else {
			*negp = false;
			lval = (unsigned long)val;
		}
		*lvalp = jiffies_to_msecs(lval);
	}
	return 0;
}
