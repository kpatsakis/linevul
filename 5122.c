static noinline int compress_file_range(struct inode *inode,
					struct page *locked_page,
					u64 start, u64 end,
					struct async_cow *async_cow,
					int *num_added)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_trans_handle *trans;
	u64 num_bytes;
	u64 blocksize = root->sectorsize;
	u64 actual_end;
	u64 isize = i_size_read(inode);
	int ret = 0;
	struct page **pages = NULL;
	unsigned long nr_pages;
	unsigned long nr_pages_ret = 0;
	unsigned long total_compressed = 0;
	unsigned long total_in = 0;
	unsigned long max_compressed = 128 * 1024;
	unsigned long max_uncompressed = 128 * 1024;
	int i;
	int will_compress;
	int compress_type = root->fs_info->compress_type;

	/* if this is a small write inside eof, kick off a defrag */
	if ((end - start + 1) < 16 * 1024 &&
	    (start > 0 || end + 1 < BTRFS_I(inode)->disk_i_size))
		btrfs_add_inode_defrag(NULL, inode);

	actual_end = min_t(u64, isize, end + 1);
again:
	will_compress = 0;
	nr_pages = (end >> PAGE_CACHE_SHIFT) - (start >> PAGE_CACHE_SHIFT) + 1;
	nr_pages = min(nr_pages, (128 * 1024UL) / PAGE_CACHE_SIZE);

	/*
	 * we don't want to send crud past the end of i_size through
	 * compression, that's just a waste of CPU time.  So, if the
	 * end of the file is before the start of our current
	 * requested range of bytes, we bail out to the uncompressed
	 * cleanup code that can deal with all of this.
	 *
	 * It isn't really the fastest way to fix things, but this is a
	 * very uncommon corner.
	 */
	if (actual_end <= start)
		goto cleanup_and_bail_uncompressed;

	total_compressed = actual_end - start;

	/* we want to make sure that amount of ram required to uncompress
	 * an extent is reasonable, so we limit the total size in ram
	 * of a compressed extent to 128k.  This is a crucial number
	 * because it also controls how easily we can spread reads across
	 * cpus for decompression.
	 *
	 * We also want to make sure the amount of IO required to do
	 * a random read is reasonably small, so we limit the size of
	 * a compressed extent to 128k.
	 */
	total_compressed = min(total_compressed, max_uncompressed);
	num_bytes = (end - start + blocksize) & ~(blocksize - 1);
	num_bytes = max(blocksize,  num_bytes);
	total_in = 0;
	ret = 0;

	/*
	 * we do compression for mount -o compress and when the
	 * inode has not been flagged as nocompress.  This flag can
	 * change at any time if we discover bad compression ratios.
	 */
	if (!(BTRFS_I(inode)->flags & BTRFS_INODE_NOCOMPRESS) &&
	    (btrfs_test_opt(root, COMPRESS) ||
	     (BTRFS_I(inode)->force_compress) ||
	     (BTRFS_I(inode)->flags & BTRFS_INODE_COMPRESS))) {
		WARN_ON(pages);
		pages = kzalloc(sizeof(struct page *) * nr_pages, GFP_NOFS);
		if (!pages) {
			/* just bail out to the uncompressed code */
			goto cont;
		}

		if (BTRFS_I(inode)->force_compress)
			compress_type = BTRFS_I(inode)->force_compress;

		ret = btrfs_compress_pages(compress_type,
					   inode->i_mapping, start,
					   total_compressed, pages,
					   nr_pages, &nr_pages_ret,
					   &total_in,
					   &total_compressed,
					   max_compressed);

		if (!ret) {
			unsigned long offset = total_compressed &
				(PAGE_CACHE_SIZE - 1);
			struct page *page = pages[nr_pages_ret - 1];
			char *kaddr;

			/* zero the tail end of the last page, we might be
			 * sending it down to disk
			 */
			if (offset) {
				kaddr = kmap_atomic(page);
				memset(kaddr + offset, 0,
				       PAGE_CACHE_SIZE - offset);
				kunmap_atomic(kaddr);
			}
			will_compress = 1;
		}
	}
cont:
	if (start == 0) {
		trans = btrfs_join_transaction(root);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			trans = NULL;
			goto cleanup_and_out;
		}
		trans->block_rsv = &root->fs_info->delalloc_block_rsv;

		/* lets try to make an inline extent */
		if (ret || total_in < (actual_end - start)) {
			/* we didn't compress the entire range, try
			 * to make an uncompressed inline extent.
			 */
			ret = cow_file_range_inline(trans, root, inode,
						    start, end, 0, 0, NULL);
		} else {
			/* try making a compressed inline extent */
			ret = cow_file_range_inline(trans, root, inode,
						    start, end,
						    total_compressed,
						    compress_type, pages);
		}
		if (ret <= 0) {
			/*
			 * inline extent creation worked or returned error,
			 * we don't need to create any more async work items.
			 * Unlock and free up our temp pages.
			 */
			extent_clear_unlock_delalloc(inode,
			     &BTRFS_I(inode)->io_tree,
			     start, end, NULL,
			     EXTENT_CLEAR_UNLOCK_PAGE | EXTENT_CLEAR_DIRTY |
			     EXTENT_CLEAR_DELALLOC |
			     EXTENT_SET_WRITEBACK | EXTENT_END_WRITEBACK);

			btrfs_end_transaction(trans, root);
			goto free_pages_out;
		}
		btrfs_end_transaction(trans, root);
	}

	if (will_compress) {
		/*
		 * we aren't doing an inline extent round the compressed size
		 * up to a block size boundary so the allocator does sane
		 * things
		 */
		total_compressed = (total_compressed + blocksize - 1) &
			~(blocksize - 1);

		/*
		 * one last check to make sure the compression is really a
		 * win, compare the page count read with the blocks on disk
		 */
		total_in = (total_in + PAGE_CACHE_SIZE - 1) &
			~(PAGE_CACHE_SIZE - 1);
		if (total_compressed >= total_in) {
			will_compress = 0;
		} else {
			num_bytes = total_in;
		}
	}
	if (!will_compress && pages) {
		/*
		 * the compression code ran but failed to make things smaller,
		 * free any pages it allocated and our page pointer array
		 */
		for (i = 0; i < nr_pages_ret; i++) {
			WARN_ON(pages[i]->mapping);
			page_cache_release(pages[i]);
		}
		kfree(pages);
		pages = NULL;
		total_compressed = 0;
		nr_pages_ret = 0;

		/* flag the file so we don't compress in the future */
		if (!btrfs_test_opt(root, FORCE_COMPRESS) &&
		    !(BTRFS_I(inode)->force_compress)) {
			BTRFS_I(inode)->flags |= BTRFS_INODE_NOCOMPRESS;
		}
	}
	if (will_compress) {
		*num_added += 1;

		/* the async work queues will take care of doing actual
		 * allocation on disk for these compressed pages,
		 * and will submit them to the elevator.
		 */
		add_async_extent(async_cow, start, num_bytes,
				 total_compressed, pages, nr_pages_ret,
				 compress_type);

		if (start + num_bytes < end) {
			start += num_bytes;
			pages = NULL;
			cond_resched();
			goto again;
		}
	} else {
cleanup_and_bail_uncompressed:
		/*
		 * No compression, but we still need to write the pages in
		 * the file we've been given so far.  redirty the locked
		 * page if it corresponds to our extent and set things up
		 * for the async work queue to run cow_file_range to do
		 * the normal delalloc dance
		 */
		if (page_offset(locked_page) >= start &&
		    page_offset(locked_page) <= end) {
			__set_page_dirty_nobuffers(locked_page);
			/* unlocked later on in the async handlers */
		}
		add_async_extent(async_cow, start, end - start + 1,
				 0, NULL, 0, BTRFS_COMPRESS_NONE);
		*num_added += 1;
	}

out:
	return ret;

free_pages_out:
	for (i = 0; i < nr_pages_ret; i++) {
		WARN_ON(pages[i]->mapping);
		page_cache_release(pages[i]);
	}
	kfree(pages);

	goto out;

cleanup_and_out:
	extent_clear_unlock_delalloc(inode, &BTRFS_I(inode)->io_tree,
				     start, end, NULL,
				     EXTENT_CLEAR_UNLOCK_PAGE |
				     EXTENT_CLEAR_DIRTY |
				     EXTENT_CLEAR_DELALLOC |
				     EXTENT_SET_WRITEBACK |
				     EXTENT_END_WRITEBACK);
	if (!trans || IS_ERR(trans))
		btrfs_error(root->fs_info, ret, "Failed to join transaction");
	else
		btrfs_abort_transaction(trans, root, ret);
	goto free_pages_out;
}
