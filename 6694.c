mm_free(struct mm_master *mm, void *address)
{
	struct mm_share *mms, *prev, tmp;

	tmp.address = address;
	mms = RB_FIND(mmtree, &mm->rb_allocated, &tmp);
	if (mms == NULL)
		fatal("mm_free(%p): can not find %p", mm, address);

	/* Debug */
	memset(mms->address, 0xd0, mms->size);

	/* Remove from allocated list and insert in free list */
	RB_REMOVE(mmtree, &mm->rb_allocated, mms);
	if (RB_INSERT(mmtree, &mm->rb_free, mms) != NULL)
		fatal("mm_free(%p): double address %p", mm, address);

	/* Find previous entry */
	prev = mms;
	if (RB_LEFT(prev, next)) {
		prev = RB_LEFT(prev, next);
		while (RB_RIGHT(prev, next))
			prev = RB_RIGHT(prev, next);
	} else {
		if (RB_PARENT(prev, next) &&
		    (prev == RB_RIGHT(RB_PARENT(prev, next), next)))
			prev = RB_PARENT(prev, next);
		else {
			while (RB_PARENT(prev, next) &&
			    (prev == RB_LEFT(RB_PARENT(prev, next), next)))
				prev = RB_PARENT(prev, next);
			prev = RB_PARENT(prev, next);
		}
	}

	/* Check if range does not overlap */
	if (prev != NULL && MM_ADDRESS_END(prev) > address)
		fatal("mm_free: memory corruption: %p(%zu) > %p",
		    prev->address, prev->size, address);

	/* See if we can merge backwards */
	if (prev != NULL && MM_ADDRESS_END(prev) == address) {
		prev->size += mms->size;
		RB_REMOVE(mmtree, &mm->rb_free, mms);
		if (mm->mmalloc == NULL)
			free(mms);
		else
			mm_free(mm->mmalloc, mms);
	} else
		prev = mms;

	if (prev == NULL)
		return;

	/* Check if we can merge forwards */
	mms = RB_NEXT(mmtree, &mm->rb_free, prev);
	if (mms == NULL)
		return;

	if (MM_ADDRESS_END(prev) > mms->address)
		fatal("mm_free: memory corruption: %p < %p(%zu)",
		    mms->address, prev->address, prev->size);
	if (MM_ADDRESS_END(prev) != mms->address)
		return;

	prev->size += mms->size;
	RB_REMOVE(mmtree, &mm->rb_free, mms);

	if (mm->mmalloc == NULL)
		free(mms);
	else
		mm_free(mm->mmalloc, mms);
}
