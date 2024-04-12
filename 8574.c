static void __dentry_kill(struct dentry *dentry)
{
	struct dentry *parent = NULL;
	bool can_free = true;
	if (!IS_ROOT(dentry))
		parent = dentry->d_parent;

	/*
	 * The dentry is now unrecoverably dead to the world.
	 */
	lockref_mark_dead(&dentry->d_lockref);

	/*
	 * inform the fs via d_prune that this dentry is about to be
	 * unhashed and destroyed.
	 */
	if (dentry->d_flags & DCACHE_OP_PRUNE)
		dentry->d_op->d_prune(dentry);

	if (dentry->d_flags & DCACHE_LRU_LIST) {
		if (!(dentry->d_flags & DCACHE_SHRINK_LIST))
			d_lru_del(dentry);
	}
	/* if it was on the hash then remove it */
	__d_drop(dentry);
	__list_del_entry(&dentry->d_child);
	/*
	 * Inform d_walk() that we are no longer attached to the
	 * dentry tree
	 */
	dentry->d_flags |= DCACHE_DENTRY_KILLED;
	if (parent)
		spin_unlock(&parent->d_lock);
	dentry_iput(dentry);
	/*
	 * dentry_iput drops the locks, at which point nobody (except
	 * transient RCU lookups) can reach this dentry.
	 */
	BUG_ON(dentry->d_lockref.count > 0);
	this_cpu_dec(nr_dentry);
	if (dentry->d_op && dentry->d_op->d_release)
		dentry->d_op->d_release(dentry);

	spin_lock(&dentry->d_lock);
	if (dentry->d_flags & DCACHE_SHRINK_LIST) {
		dentry->d_flags |= DCACHE_MAY_FREE;
		can_free = false;
	}
	spin_unlock(&dentry->d_lock);
	if (likely(can_free))
		dentry_free(dentry);
}