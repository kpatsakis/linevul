static noinline void copy_for_split(struct btrfs_trans_handle *trans,
				    struct btrfs_root *root,
				    struct btrfs_path *path,
				    struct extent_buffer *l,
				    struct extent_buffer *right,
				    int slot, int mid, int nritems)
{
	int data_copy_size;
	int rt_data_off;
	int i;
	struct btrfs_disk_key disk_key;
	struct btrfs_map_token token;

	btrfs_init_map_token(&token);

	nritems = nritems - mid;
	btrfs_set_header_nritems(right, nritems);
	data_copy_size = btrfs_item_end_nr(l, mid) - leaf_data_end(root, l);

	copy_extent_buffer(right, l, btrfs_item_nr_offset(0),
			   btrfs_item_nr_offset(mid),
			   nritems * sizeof(struct btrfs_item));

	copy_extent_buffer(right, l,
		     btrfs_leaf_data(right) + BTRFS_LEAF_DATA_SIZE(root) -
		     data_copy_size, btrfs_leaf_data(l) +
		     leaf_data_end(root, l), data_copy_size);

	rt_data_off = BTRFS_LEAF_DATA_SIZE(root) -
		      btrfs_item_end_nr(l, mid);

	for (i = 0; i < nritems; i++) {
		struct btrfs_item *item = btrfs_item_nr(i);
		u32 ioff;

		ioff = btrfs_token_item_offset(right, item, &token);
		btrfs_set_token_item_offset(right, item,
					    ioff + rt_data_off, &token);
	}

	btrfs_set_header_nritems(l, mid);
	btrfs_item_key(right, &disk_key, 0);
	insert_ptr(trans, root, path, &disk_key, right->start,
		   path->slots[1] + 1, 1);

	btrfs_mark_buffer_dirty(right);
	btrfs_mark_buffer_dirty(l);
	BUG_ON(path->slots[0] != slot);

	if (mid <= slot) {
		btrfs_tree_unlock(path->nodes[0]);
		free_extent_buffer(path->nodes[0]);
		path->nodes[0] = right;
		path->slots[0] -= mid;
		path->slots[1] += 1;
	} else {
		btrfs_tree_unlock(right);
		free_extent_buffer(right);
	}

	BUG_ON(path->slots[0] < 0);
}
