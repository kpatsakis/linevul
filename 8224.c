static int hfsplus_create(struct inode *dir, struct dentry *dentry, umode_t mode,
			  struct nameidata *nd)
{
	return hfsplus_mknod(dir, dentry, mode, 0);
}
