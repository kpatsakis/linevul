static inline void fixup_objfreelist_debug(struct kmem_cache *cachep,
						void **list)
{
#if DEBUG
	void *next = *list;
	void *objp;

	while (next) {
		objp = next - obj_offset(cachep);
		next = *(void **)next;
		poison_obj(cachep, objp, POISON_FREE);
	}
#endif
}
