static int hfsplus_unlink(struct inode *dir, struct dentry *dentry)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	struct inode *inode = dentry->d_inode;
	struct qstr str;
	char name[32];
	u32 cnid;
	int res;

	if (HFSPLUS_IS_RSRC(inode))
		return -EPERM;

	mutex_lock(&sbi->vh_mutex);
	cnid = (u32)(unsigned long)dentry->d_fsdata;
	if (inode->i_ino == cnid &&
	    atomic_read(&HFSPLUS_I(inode)->opencnt)) {
		str.name = name;
		str.len = sprintf(name, "temp%lu", inode->i_ino);
		res = hfsplus_rename_cat(inode->i_ino,
					 dir, &dentry->d_name,
					 sbi->hidden_dir, &str);
		if (!res) {
			inode->i_flags |= S_DEAD;
			drop_nlink(inode);
		}
		goto out;
	}
	res = hfsplus_delete_cat(cnid, dir, &dentry->d_name);
	if (res)
		goto out;

	if (inode->i_nlink > 0)
		drop_nlink(inode);
	if (inode->i_ino == cnid)
		clear_nlink(inode);
	if (!inode->i_nlink) {
		if (inode->i_ino != cnid) {
			sbi->file_count--;
			if (!atomic_read(&HFSPLUS_I(inode)->opencnt)) {
				res = hfsplus_delete_cat(inode->i_ino,
							 sbi->hidden_dir,
							 NULL);
				if (!res)
					hfsplus_delete_inode(inode);
			} else
				inode->i_flags |= S_DEAD;
		} else
			hfsplus_delete_inode(inode);
	} else
		sbi->file_count--;
	inode->i_ctime = CURRENT_TIME_SEC;
	mark_inode_dirty(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	return res;
}
