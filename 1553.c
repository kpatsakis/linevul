slab_out_of_memory(struct kmem_cache *cachep, gfp_t gfpflags, int nodeid)
{
#if DEBUG
	struct kmem_cache_node *n;
	unsigned long flags;
	int node;
	static DEFINE_RATELIMIT_STATE(slab_oom_rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);

	if ((gfpflags & __GFP_NOWARN) || !__ratelimit(&slab_oom_rs))
		return;

	pr_warn("SLAB: Unable to allocate memory on node %d, gfp=%#x(%pGg)\n",
		nodeid, gfpflags, &gfpflags);
	pr_warn("  cache: %s, object size: %d, order: %d\n",
		cachep->name, cachep->size, cachep->gfporder);

	for_each_kmem_cache_node(cachep, node, n) {
		unsigned long total_slabs, free_slabs, free_objs;

		spin_lock_irqsave(&n->list_lock, flags);
		total_slabs = n->total_slabs;
		free_slabs = n->free_slabs;
		free_objs = n->free_objects;
		spin_unlock_irqrestore(&n->list_lock, flags);

		pr_warn("  node %d: slabs: %ld/%ld, objs: %ld/%ld\n",
			node, total_slabs - free_slabs, total_slabs,
			(total_slabs * cachep->num) - free_objs,
			total_slabs * cachep->num);
	}
#endif
}
