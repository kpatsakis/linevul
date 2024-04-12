static int read_reset_stat(struct ctl_table *table, int write,
			   void __user *buffer, size_t *lenp,
			   loff_t *ppos)
{
	atomic_t *stat = (atomic_t *)table->data;

	if (!stat)
		return -EINVAL;

	if (write)
		atomic_set(stat, 0);
	else {
		char str_buf[32];
		char *data;
		int len = snprintf(str_buf, 32, "%d\n", atomic_read(stat));
		if (len >= 32)
			return -EFAULT;
		len = strlen(str_buf);
		if (*ppos > len) {
			*lenp = 0;
			return 0;
		}
		data = &str_buf[*ppos];
		len -= *ppos;
		if (len > *lenp)
			len = *lenp;
		if (len && copy_to_user(buffer, str_buf, len))
			return -EFAULT;
		*lenp = len;
		*ppos += len;
	}
	return 0;
}
