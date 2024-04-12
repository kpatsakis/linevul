xfs_attr_list(
	xfs_inode_t	*dp,
	char		*buffer,
	int		bufsize,
	int		flags,
	attrlist_cursor_kern_t *cursor)
{
	xfs_attr_list_context_t context;
	struct attrlist *alist;
	int error;

	/*
	 * Validate the cursor.
	 */
	if (cursor->pad1 || cursor->pad2)
		return -EINVAL;
	if ((cursor->initted == 0) &&
	    (cursor->hashval || cursor->blkno || cursor->offset))
		return -EINVAL;

	/*
	 * Check for a properly aligned buffer.
	 */
	if (((long)buffer) & (sizeof(int)-1))
		return -EFAULT;
	if (flags & ATTR_KERNOVAL)
		bufsize = 0;

	/*
	 * Initialize the output buffer.
	 */
	memset(&context, 0, sizeof(context));
	context.dp = dp;
	context.cursor = cursor;
	context.resynch = 1;
	context.flags = flags;
	context.alist = buffer;
	context.bufsize = (bufsize & ~(sizeof(int)-1));  /* align */
	context.firstu = context.bufsize;
	context.put_listent = xfs_attr_put_listent;

	alist = (struct attrlist *)context.alist;
	alist->al_count = 0;
	alist->al_more = 0;
	alist->al_offset[0] = context.bufsize;

	error = xfs_attr_list_int(&context);
	ASSERT(error <= 0);
	return error;
}
