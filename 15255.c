ssize_t btrfs_getxattr(struct dentry *dentry, const char *name,
		       void *buffer, size_t size)
{
	/*
	 * If this is a request for a synthetic attribute in the system.*
	 * namespace use the generic infrastructure to resolve a handler
	 * for it via sb->s_xattr.
	 */
	if (!strncmp(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		return generic_getxattr(dentry, name, buffer, size);

	if (!btrfs_is_valid_xattr(name))
		return -EOPNOTSUPP;
	return __btrfs_getxattr(dentry->d_inode, name, buffer, size);
}
