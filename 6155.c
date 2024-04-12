static inline int dentry_cmp(const struct dentry *dentry, const unsigned char *ct, unsigned tcount)
{
	const unsigned char *cs;
	/*
	 * Be careful about RCU walk racing with rename:
	 * use ACCESS_ONCE to fetch the name pointer.
	 *
	 * NOTE! Even if a rename will mean that the length
	 * was not loaded atomically, we don't care. The
	 * RCU walk will check the sequence count eventually,
	 * and catch it. And we won't overrun the buffer,
	 * because we're reading the name pointer atomically,
	 * and a dentry name is guaranteed to be properly
	 * terminated with a NUL byte.
	 *
	 * End result: even if 'len' is wrong, we'll exit
	 * early because the data cannot match (there can
	 * be no NUL in the ct/tcount data)
	 */
	cs = ACCESS_ONCE(dentry->d_name.name);
	smp_read_barrier_depends();
	return dentry_string_cmp(cs, ct, tcount);
}