int cifs_flush(struct file *file, fl_owner_t id)
{
	struct inode *inode = file_inode(file);
	int rc = 0;

	if (file->f_mode & FMODE_WRITE)
		rc = filemap_write_and_wait(inode->i_mapping);

	cifs_dbg(FYI, "Flush inode %p file %p rc %d\n", inode, file, rc);

	return rc;
}
