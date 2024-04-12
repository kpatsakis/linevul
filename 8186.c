int proc_doulongvec_ms_jiffies_minmax(struct ctl_table *table, int write,
				      void __user *buffer,
				      size_t *lenp, loff_t *ppos)
{
    return do_proc_doulongvec_minmax(table, write, buffer,
				     lenp, ppos, HZ, 1000l);
}
