void propagate_mount_unlock(struct mount *mnt)
{
	struct mount *parent = mnt->mnt_parent;
	struct mount *m, *child;

	BUG_ON(parent == mnt);

	for (m = propagation_next(parent, parent); m;
			m = propagation_next(m, parent)) {
		child = __lookup_mnt_last(&m->mnt, mnt->mnt_mountpoint);
		if (child)
			child->mnt.mnt_flags &= ~MNT_LOCKED;
	}
}
