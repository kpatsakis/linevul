static void commit_list_insert_by_date_cached(struct commit *p, struct commit_list **head,
		    struct commit_list *cached_base, struct commit_list **cache)
{
	struct commit_list *new_entry;

	if (cached_base && p->date < cached_base->item->date)
		new_entry = commit_list_insert_by_date(p, &cached_base->next);
	else
		new_entry = commit_list_insert_by_date(p, head);

	if (cache && (!*cache || p->date < (*cache)->item->date))
		*cache = new_entry;
}
