static int btrfs_add_nondir(struct btrfs_trans_handle *trans,
			    struct inode *dir, struct dentry *dentry,
			    struct inode *inode, int backref, u64 index)
{
	int err = btrfs_add_link(trans, dir, inode,
				 dentry->d_name.name, dentry->d_name.len,
				 backref, index);
	if (err > 0)
		err = -EEXIST;
	return err;
}
