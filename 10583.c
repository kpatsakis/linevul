static int hugetlbfs_mknod(struct inode *dir,
			struct dentry *dentry, umode_t mode, dev_t dev)
{
	struct inode *inode;
	int error = -ENOSPC;

	inode = hugetlbfs_get_inode(dir->i_sb, dir, mode, dev);
	if (inode) {
		dir->i_ctime = dir->i_mtime = CURRENT_TIME;
		d_instantiate(dentry, inode);
		dget(dentry);	/* Extra count - pin the dentry in core */
		error = 0;
	}
	return error;
}
