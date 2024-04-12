static int blkdev_releasepage(struct page *page, gfp_t wait)
{
	struct super_block *super = BDEV_I(page->mapping->host)->bdev.bd_super;

	if (super && super->s_op->bdev_try_to_free_page)
		return super->s_op->bdev_try_to_free_page(super, page, wait);

	return try_to_free_buffers(page);
}
