static bool set_on_slab_cache(struct kmem_cache *cachep,
			size_t size, unsigned long flags)
{
	size_t left;

	cachep->num = 0;

	left = calculate_slab_order(cachep, size, flags);
	if (!cachep->num)
		return false;

	cachep->colour = left / cachep->colour_off;

	return true;
}
