static ssize_t hugetlbfs_read(struct file *filp, char __user *buf,
			      size_t len, loff_t *ppos)
{
	struct hstate *h = hstate_file(filp);
	struct address_space *mapping = filp->f_mapping;
	struct inode *inode = mapping->host;
	unsigned long index = *ppos >> huge_page_shift(h);
	unsigned long offset = *ppos & ~huge_page_mask(h);
	unsigned long end_index;
	loff_t isize;
	ssize_t retval = 0;

	/* validate length */
	if (len == 0)
		goto out;

	for (;;) {
		struct page *page;
		unsigned long nr, ret;
		int ra;

		/* nr is the maximum number of bytes to copy from this page */
		nr = huge_page_size(h);
		isize = i_size_read(inode);
		if (!isize)
			goto out;
		end_index = (isize - 1) >> huge_page_shift(h);
		if (index >= end_index) {
			if (index > end_index)
				goto out;
			nr = ((isize - 1) & ~huge_page_mask(h)) + 1;
			if (nr <= offset)
				goto out;
		}
		nr = nr - offset;

		/* Find the page */
		page = find_lock_page(mapping, index);
		if (unlikely(page == NULL)) {
			/*
			 * We have a HOLE, zero out the user-buffer for the
			 * length of the hole or request.
			 */
			ret = len < nr ? len : nr;
			if (clear_user(buf, ret))
				ra = -EFAULT;
			else
				ra = 0;
		} else {
			unlock_page(page);

			/*
			 * We have the page, copy it to user space buffer.
			 */
			ra = hugetlbfs_read_actor(page, offset, buf, len, nr);
			ret = ra;
			page_cache_release(page);
		}
		if (ra < 0) {
			if (retval == 0)
				retval = ra;
			goto out;
		}

		offset += ret;
		retval += ret;
		len -= ret;
		index += offset >> huge_page_shift(h);
		offset &= ~huge_page_mask(h);

		/* short read or no more work */
		if ((ret != nr) || (len == 0))
			break;
	}
out:
	*ppos = ((loff_t)index << huge_page_shift(h)) + offset;
	return retval;
}
