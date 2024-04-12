static struct array_cache *alloc_arraycache(int node, int entries,
					    int batchcount, gfp_t gfp)
{
	size_t memsize = sizeof(void *) * entries + sizeof(struct array_cache);
	struct array_cache *ac = NULL;

	ac = kmalloc_node(memsize, gfp, node);
	init_arraycache(ac, entries, batchcount);
	return ac;
}
