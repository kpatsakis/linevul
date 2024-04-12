static void drain_array_locked(struct kmem_cache *cachep, struct array_cache *ac,
				int node, bool free_all, struct list_head *list)
{
	int tofree;

	if (!ac || !ac->avail)
		return;

	tofree = free_all ? ac->avail : (ac->limit + 4) / 5;
	if (tofree > ac->avail)
		tofree = (ac->avail + 1) / 2;

	free_block(cachep, ac->entry, tofree, node, list);
	ac->avail -= tofree;
	memmove(ac->entry, &(ac->entry[tofree]), sizeof(void *) * ac->avail);
}
