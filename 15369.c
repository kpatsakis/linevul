static void cache_init_objs(struct kmem_cache *cachep,
			    struct page *page)
{
	int i;
	void *objp;
	bool shuffled;

	cache_init_objs_debug(cachep, page);

	/* Try to randomize the freelist if enabled */
	shuffled = shuffle_freelist(cachep, page);

	if (!shuffled && OBJFREELIST_SLAB(cachep)) {
		page->freelist = index_to_obj(cachep, page, cachep->num - 1) +
						obj_offset(cachep);
	}

	for (i = 0; i < cachep->num; i++) {
		objp = index_to_obj(cachep, page, i);
		kasan_init_slab_obj(cachep, objp);

		/* constructor could break poison info */
		if (DEBUG == 0 && cachep->ctor) {
			kasan_unpoison_object_data(cachep, objp);
			cachep->ctor(objp);
			kasan_poison_object_data(cachep, objp);
		}

		if (!shuffled)
			set_free_obj(page, i, i);
	}
}
