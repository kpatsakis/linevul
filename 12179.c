static int btrfs_readpage_end_io_hook(struct page *page, u64 start, u64 end,
			       struct extent_state *state, int mirror)
{
	size_t offset = start - ((u64)page->index << PAGE_CACHE_SHIFT);
	struct inode *inode = page->mapping->host;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	char *kaddr;
	u64 private = ~(u32)0;
	int ret;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	u32 csum = ~(u32)0;

	if (PageChecked(page)) {
		ClearPageChecked(page);
		goto good;
	}

	if (BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM)
		goto good;

	if (root->root_key.objectid == BTRFS_DATA_RELOC_TREE_OBJECTID &&
	    test_range_bit(io_tree, start, end, EXTENT_NODATASUM, 1, NULL)) {
		clear_extent_bits(io_tree, start, end, EXTENT_NODATASUM,
				  GFP_NOFS);
		return 0;
	}

	if (state && state->start == start) {
		private = state->private;
		ret = 0;
	} else {
		ret = get_state_private(io_tree, start, &private);
	}
	kaddr = kmap_atomic(page);
	if (ret)
		goto zeroit;

	csum = btrfs_csum_data(root, kaddr + offset, csum,  end - start + 1);
	btrfs_csum_final(csum, (char *)&csum);
	if (csum != private)
		goto zeroit;

	kunmap_atomic(kaddr);
good:
	return 0;

zeroit:
	printk_ratelimited(KERN_INFO "btrfs csum failed ino %llu off %llu csum %u "
		       "private %llu\n",
		       (unsigned long long)btrfs_ino(page->mapping->host),
		       (unsigned long long)start, csum,
		       (unsigned long long)private);
	memset(kaddr + offset, 1, end - start + 1);
	flush_dcache_page(page);
	kunmap_atomic(kaddr);
	if (private == 0)
		return 0;
	return -EIO;
}
