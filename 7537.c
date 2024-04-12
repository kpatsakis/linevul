static int gfs2_allocate_page_backing(struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct buffer_head bh;
	unsigned long size = PAGE_CACHE_SIZE;
	u64 lblock = page->index << (PAGE_CACHE_SHIFT - inode->i_blkbits);

	do {
		bh.b_state = 0;
		bh.b_size = size;
		gfs2_block_map(inode, lblock, &bh, 1);
		if (!buffer_mapped(&bh))
			return -EIO;
		size -= bh.b_size;
		lblock += (bh.b_size >> inode->i_blkbits);
	} while(size > 0);
	return 0;
}
