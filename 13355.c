static int btrfs_finish_ordered_io(struct btrfs_ordered_extent *ordered_extent)
{
	struct inode *inode = ordered_extent->inode;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_trans_handle *trans = NULL;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct extent_state *cached_state = NULL;
	int compress_type = 0;
	int ret;
	bool nolock;

	nolock = btrfs_is_free_space_inode(inode);

	if (test_bit(BTRFS_ORDERED_IOERR, &ordered_extent->flags)) {
		ret = -EIO;
		goto out;
	}

	if (test_bit(BTRFS_ORDERED_NOCOW, &ordered_extent->flags)) {
		BUG_ON(!list_empty(&ordered_extent->list)); /* Logic error */
		btrfs_ordered_update_i_size(inode, 0, ordered_extent);
		if (nolock)
			trans = btrfs_join_transaction_nolock(root);
		else
			trans = btrfs_join_transaction(root);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			trans = NULL;
			goto out;
		}
		trans->block_rsv = &root->fs_info->delalloc_block_rsv;
		ret = btrfs_update_inode_fallback(trans, root, inode);
		if (ret) /* -ENOMEM or corruption */
			btrfs_abort_transaction(trans, root, ret);
		goto out;
	}

	lock_extent_bits(io_tree, ordered_extent->file_offset,
			 ordered_extent->file_offset + ordered_extent->len - 1,
			 0, &cached_state);

	if (nolock)
		trans = btrfs_join_transaction_nolock(root);
	else
		trans = btrfs_join_transaction(root);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		trans = NULL;
		goto out_unlock;
	}
	trans->block_rsv = &root->fs_info->delalloc_block_rsv;

	if (test_bit(BTRFS_ORDERED_COMPRESSED, &ordered_extent->flags))
		compress_type = ordered_extent->compress_type;
	if (test_bit(BTRFS_ORDERED_PREALLOC, &ordered_extent->flags)) {
		BUG_ON(compress_type);
		ret = btrfs_mark_extent_written(trans, inode,
						ordered_extent->file_offset,
						ordered_extent->file_offset +
						ordered_extent->len);
	} else {
		BUG_ON(root == root->fs_info->tree_root);
		ret = insert_reserved_file_extent(trans, inode,
						ordered_extent->file_offset,
						ordered_extent->start,
						ordered_extent->disk_len,
						ordered_extent->len,
						ordered_extent->len,
						compress_type, 0, 0,
						BTRFS_FILE_EXTENT_REG);
	}
	unpin_extent_cache(&BTRFS_I(inode)->extent_tree,
			   ordered_extent->file_offset, ordered_extent->len,
			   trans->transid);
	if (ret < 0) {
		btrfs_abort_transaction(trans, root, ret);
		goto out_unlock;
	}

	add_pending_csums(trans, inode, ordered_extent->file_offset,
			  &ordered_extent->list);

	btrfs_ordered_update_i_size(inode, 0, ordered_extent);
	ret = btrfs_update_inode_fallback(trans, root, inode);
	if (ret) { /* -ENOMEM or corruption */
		btrfs_abort_transaction(trans, root, ret);
		goto out_unlock;
	}
	ret = 0;
out_unlock:
	unlock_extent_cached(io_tree, ordered_extent->file_offset,
			     ordered_extent->file_offset +
			     ordered_extent->len - 1, &cached_state, GFP_NOFS);
out:
	if (root != root->fs_info->tree_root)
		btrfs_delalloc_release_metadata(inode, ordered_extent->len);
	if (trans)
		btrfs_end_transaction(trans, root);

	if (ret)
		clear_extent_uptodate(io_tree, ordered_extent->file_offset,
				      ordered_extent->file_offset +
				      ordered_extent->len - 1, NULL, GFP_NOFS);

	/*
	 * This needs to be done to make sure anybody waiting knows we are done
	 * updating everything for this ordered extent.
	 */
	btrfs_remove_ordered_extent(inode, ordered_extent);

	/* once for us */
	btrfs_put_ordered_extent(ordered_extent);
	/* once for the tree */
	btrfs_put_ordered_extent(ordered_extent);

	return ret;
}
