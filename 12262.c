void swap_free(swp_entry_t entry)
{
	struct swap_info_struct *p;

	p = swap_info_get(entry);
	if (p) {
		swap_entry_free(p, entry, 1);
		spin_unlock(&swap_lock);
	}
}
