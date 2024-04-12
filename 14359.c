static int unix_mknod(const char *sun_path, umode_t mode, struct path *res)
{
	struct dentry *dentry;
	struct path path;
	int err = 0;
	/*
	 * Get the parent directory, calculate the hash for last
	 * component.
	 */
	dentry = kern_path_create(AT_FDCWD, sun_path, &path, 0);
	err = PTR_ERR(dentry);
	if (IS_ERR(dentry))
		return err;

	/*
	 * All right, let's create it.
	 */
	err = security_path_mknod(&path, dentry, mode, 0);
	if (!err) {
		err = vfs_mknod(d_inode(path.dentry), dentry, mode, 0);
		if (!err) {
			res->mnt = mntget(path.mnt);
			res->dentry = dget(dentry);
		}
	}
	done_path_create(&path, dentry);
	return err;
}
