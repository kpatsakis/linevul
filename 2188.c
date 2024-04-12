static int compat_calc_entry(const struct ipt_entry *e,
			     const struct xt_table_info *info,
			     const void *base, struct xt_table_info *newinfo)
{
	const struct xt_entry_match *ematch;
	const struct xt_entry_target *t;
	unsigned int entry_offset;
	int off, i, ret;

	off = sizeof(struct ipt_entry) - sizeof(struct compat_ipt_entry);
	entry_offset = (void *)e - base;
	xt_ematch_foreach(ematch, e)
		off += xt_compat_match_offset(ematch->u.kernel.match);
	t = ipt_get_target_c(e);
	off += xt_compat_target_offset(t->u.kernel.target);
	newinfo->size -= off;
	ret = xt_compat_add_offset(AF_INET, entry_offset, off);
	if (ret)
		return ret;

	for (i = 0; i < NF_INET_NUMHOOKS; i++) {
		if (info->hook_entry[i] &&
		    (e < (struct ipt_entry *)(base + info->hook_entry[i])))
			newinfo->hook_entry[i] -= off;
		if (info->underflow[i] &&
		    (e < (struct ipt_entry *)(base + info->underflow[i])))
			newinfo->underflow[i] -= off;
	}
	return 0;
}
