long ext4_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	handle_t *handle;
	loff_t new_size;
	unsigned int max_blocks;
	int ret = 0;
	int ret2 = 0;
	int retries = 0;
	int flags;
	struct ext4_map_blocks map;
	unsigned int credits, blkbits = inode->i_blkbits;

	/*
	 * currently supporting (pre)allocate mode for extent-based
	 * files _only_
	 */
	if (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		return -EOPNOTSUPP;

	/* Return error if mode is not supported */
	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		return -EOPNOTSUPP;

	if (mode & FALLOC_FL_PUNCH_HOLE)
		return ext4_punch_hole(file, offset, len);

	trace_ext4_fallocate_enter(inode, offset, len, mode);
	map.m_lblk = offset >> blkbits;
	/*
	 * We can't just convert len to max_blocks because
	 * If blocksize = 4096 offset = 3072 and len = 2048
	 */
	max_blocks = (EXT4_BLOCK_ALIGN(len + offset, blkbits) >> blkbits)
		- map.m_lblk;
	/*
	 * credits to insert 1 extent into extent tree
	 */
	credits = ext4_chunk_trans_blocks(inode, max_blocks);
	mutex_lock(&inode->i_mutex);
	ret = inode_newsize_ok(inode, (len + offset));
	if (ret) {
		mutex_unlock(&inode->i_mutex);
		trace_ext4_fallocate_exit(inode, offset, max_blocks, ret);
		return ret;
	}
	flags = EXT4_GET_BLOCKS_CREATE_UNINIT_EXT;
	if (mode & FALLOC_FL_KEEP_SIZE)
		flags |= EXT4_GET_BLOCKS_KEEP_SIZE;
	/*
	 * Don't normalize the request if it can fit in one extent so
	 * that it doesn't get unnecessarily split into multiple
	 * extents.
	 */
	if (len <= EXT_UNINIT_MAX_LEN << blkbits)
		flags |= EXT4_GET_BLOCKS_NO_NORMALIZE;

	/* Prevent race condition between unwritten */
	ext4_flush_unwritten_io(inode);
retry:
	while (ret >= 0 && ret < max_blocks) {
		map.m_lblk = map.m_lblk + ret;
		map.m_len = max_blocks = max_blocks - ret;
		handle = ext4_journal_start(inode, credits);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			break;
		}
		ret = ext4_map_blocks(handle, inode, &map, flags);
		if (ret <= 0) {
#ifdef EXT4FS_DEBUG
			WARN_ON(ret <= 0);
			printk(KERN_ERR "%s: ext4_ext_map_blocks "
				    "returned error inode#%lu, block=%u, "
				    "max_blocks=%u", __func__,
				    inode->i_ino, map.m_lblk, max_blocks);
#endif
			ext4_mark_inode_dirty(handle, inode);
			ret2 = ext4_journal_stop(handle);
			break;
		}
		if ((map.m_lblk + ret) >= (EXT4_BLOCK_ALIGN(offset + len,
						blkbits) >> blkbits))
			new_size = offset + len;
		else
			new_size = ((loff_t) map.m_lblk + ret) << blkbits;

		ext4_falloc_update_inode(inode, mode, new_size,
					 (map.m_flags & EXT4_MAP_NEW));
		ext4_mark_inode_dirty(handle, inode);
		if ((file->f_flags & O_SYNC) && ret >= max_blocks)
			ext4_handle_sync(handle);
		ret2 = ext4_journal_stop(handle);
		if (ret2)
			break;
	}
	if (ret == -ENOSPC &&
			ext4_should_retry_alloc(inode->i_sb, &retries)) {
		ret = 0;
		goto retry;
	}
	mutex_unlock(&inode->i_mutex);
	trace_ext4_fallocate_exit(inode, offset, max_blocks,
				ret > 0 ? ret2 : ret);
	return ret > 0 ? ret2 : ret;
}
