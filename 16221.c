int jffs2_init_acl_pre(struct inode *dir_i, struct inode *inode, umode_t *i_mode)
{
	struct posix_acl *default_acl, *acl;
	int rc;

	cache_no_acl(inode);

	rc = posix_acl_create(dir_i, i_mode, &default_acl, &acl);
	if (rc)
		return rc;

	if (default_acl) {
		set_cached_acl(inode, ACL_TYPE_DEFAULT, default_acl);
		posix_acl_release(default_acl);
	}
	if (acl) {
		set_cached_acl(inode, ACL_TYPE_ACCESS, acl);
		posix_acl_release(acl);
	}
	return 0;
}
