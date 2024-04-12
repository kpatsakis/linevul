static inline int check_entry_size_and_hooks(struct arpt_entry *e,
					     struct xt_table_info *newinfo,
					     const unsigned char *base,
					     const unsigned char *limit,
					     const unsigned int *hook_entries,
					     const unsigned int *underflows,
					     unsigned int valid_hooks)
{
	unsigned int h;
	int err;

	if ((unsigned long)e % __alignof__(struct arpt_entry) != 0 ||
	    (unsigned char *)e + sizeof(struct arpt_entry) >= limit ||
	    (unsigned char *)e + e->next_offset > limit)
		return -EINVAL;

	if (e->next_offset
	    < sizeof(struct arpt_entry) + sizeof(struct xt_entry_target))
		return -EINVAL;

	if (!arp_checkentry(&e->arp))
		return -EINVAL;

	err = xt_check_entry_offsets(e, e->elems, e->target_offset,
				     e->next_offset);
	if (err)
		return err;

	/* Check hooks & underflows */
	for (h = 0; h < NF_ARP_NUMHOOKS; h++) {
		if (!(valid_hooks & (1 << h)))
			continue;
		if ((unsigned char *)e - base == hook_entries[h])
			newinfo->hook_entry[h] = hook_entries[h];
		if ((unsigned char *)e - base == underflows[h]) {
			if (!check_underflow(e))
				return -EINVAL;

			newinfo->underflow[h] = underflows[h];
		}
	}

	/* Clear counters and comefrom */
	e->counters = ((struct xt_counters) { 0, 0 });
	e->comefrom = 0;
	return 0;
}