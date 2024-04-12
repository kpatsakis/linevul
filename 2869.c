struct posix_acl *ocfs2_iop_get_acl(struct inode *inode, int type)
{
	struct ocfs2_super *osb;
	struct buffer_head *di_bh = NULL;
	struct posix_acl *acl;
	int ret;

	osb = OCFS2_SB(inode->i_sb);
	if (!(osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL))
		return NULL;
	ret = ocfs2_inode_lock(inode, &di_bh, 0);
	if (ret < 0) {
		if (ret != -ENOENT)
			mlog_errno(ret);
		return ERR_PTR(ret);
	}

	acl = ocfs2_get_acl_nolock(inode, type, di_bh);

	ocfs2_inode_unlock(inode, 0);
	brelse(di_bh);
	return acl;
}
