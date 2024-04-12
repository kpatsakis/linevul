static int btrfs_getattr(struct vfsmount *mnt,
			 struct dentry *dentry, struct kstat *stat)
{
	struct inode *inode = dentry->d_inode;
	u32 blocksize = inode->i_sb->s_blocksize;

	generic_fillattr(inode, stat);
	stat->dev = BTRFS_I(inode)->root->anon_dev;
	stat->blksize = PAGE_CACHE_SIZE;
	stat->blocks = (ALIGN(inode_get_bytes(inode), blocksize) +
		ALIGN(BTRFS_I(inode)->delalloc_bytes, blocksize)) >> 9;
	return 0;
}
