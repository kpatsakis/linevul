mm_make_entry(struct mm_master *mm, struct mmtree *head,
    void *address, size_t size)
{
	struct mm_share *tmp, *tmp2;

	if (mm->mmalloc == NULL)
		tmp = xcalloc(1, sizeof(struct mm_share));
	else
		tmp = mm_xmalloc(mm->mmalloc, sizeof(struct mm_share));
	tmp->address = address;
	tmp->size = size;

	tmp2 = RB_INSERT(mmtree, head, tmp);
	if (tmp2 != NULL)
		fatal("mm_make_entry(%p): double address %p->%p(%zu)",
		    mm, tmp2, address, size);

	return (tmp);
}
