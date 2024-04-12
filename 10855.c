static void jffs2_iset_acl(struct inode *inode, struct posix_acl **i_acl, struct posix_acl *acl)
{
	spin_lock(&inode->i_lock);
	if (*i_acl != JFFS2_ACL_NOT_CACHED)
		posix_acl_release(*i_acl);
	*i_acl = posix_acl_dup(acl);
        spin_unlock(&inode->i_lock);
 }
