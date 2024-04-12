int btrfs_compare_trees(struct btrfs_root *left_root,
			struct btrfs_root *right_root,
			btrfs_changed_cb_t changed_cb, void *ctx)
{
	int ret;
	int cmp;
	struct btrfs_path *left_path = NULL;
	struct btrfs_path *right_path = NULL;
	struct btrfs_key left_key;
	struct btrfs_key right_key;
	char *tmp_buf = NULL;
	int left_root_level;
	int right_root_level;
	int left_level;
	int right_level;
	int left_end_reached;
	int right_end_reached;
	int advance_left;
	int advance_right;
	u64 left_blockptr;
	u64 right_blockptr;
	u64 left_gen;
	u64 right_gen;

	left_path = btrfs_alloc_path();
	if (!left_path) {
		ret = -ENOMEM;
		goto out;
	}
	right_path = btrfs_alloc_path();
	if (!right_path) {
		ret = -ENOMEM;
		goto out;
	}

	tmp_buf = kmalloc(left_root->nodesize, GFP_NOFS);
	if (!tmp_buf) {
		ret = -ENOMEM;
		goto out;
	}

	left_path->search_commit_root = 1;
	left_path->skip_locking = 1;
	right_path->search_commit_root = 1;
	right_path->skip_locking = 1;

	/*
	 * Strategy: Go to the first items of both trees. Then do
	 *
	 * If both trees are at level 0
	 *   Compare keys of current items
	 *     If left < right treat left item as new, advance left tree
	 *       and repeat
	 *     If left > right treat right item as deleted, advance right tree
	 *       and repeat
	 *     If left == right do deep compare of items, treat as changed if
	 *       needed, advance both trees and repeat
	 * If both trees are at the same level but not at level 0
	 *   Compare keys of current nodes/leafs
	 *     If left < right advance left tree and repeat
	 *     If left > right advance right tree and repeat
	 *     If left == right compare blockptrs of the next nodes/leafs
	 *       If they match advance both trees but stay at the same level
	 *         and repeat
	 *       If they don't match advance both trees while allowing to go
	 *         deeper and repeat
	 * If tree levels are different
	 *   Advance the tree that needs it and repeat
	 *
	 * Advancing a tree means:
	 *   If we are at level 0, try to go to the next slot. If that's not
	 *   possible, go one level up and repeat. Stop when we found a level
	 *   where we could go to the next slot. We may at this point be on a
	 *   node or a leaf.
	 *
	 *   If we are not at level 0 and not on shared tree blocks, go one
	 *   level deeper.
	 *
	 *   If we are not at level 0 and on shared tree blocks, go one slot to
	 *   the right if possible or go up and right.
	 */

	down_read(&left_root->fs_info->commit_root_sem);
	left_level = btrfs_header_level(left_root->commit_root);
	left_root_level = left_level;
	left_path->nodes[left_level] = left_root->commit_root;
	extent_buffer_get(left_path->nodes[left_level]);

	right_level = btrfs_header_level(right_root->commit_root);
	right_root_level = right_level;
	right_path->nodes[right_level] = right_root->commit_root;
	extent_buffer_get(right_path->nodes[right_level]);
	up_read(&left_root->fs_info->commit_root_sem);

	if (left_level == 0)
		btrfs_item_key_to_cpu(left_path->nodes[left_level],
				&left_key, left_path->slots[left_level]);
	else
		btrfs_node_key_to_cpu(left_path->nodes[left_level],
				&left_key, left_path->slots[left_level]);
	if (right_level == 0)
		btrfs_item_key_to_cpu(right_path->nodes[right_level],
				&right_key, right_path->slots[right_level]);
	else
		btrfs_node_key_to_cpu(right_path->nodes[right_level],
				&right_key, right_path->slots[right_level]);

	left_end_reached = right_end_reached = 0;
	advance_left = advance_right = 0;

	while (1) {
		if (advance_left && !left_end_reached) {
			ret = tree_advance(left_root, left_path, &left_level,
					left_root_level,
					advance_left != ADVANCE_ONLY_NEXT,
					&left_key);
			if (ret < 0)
				left_end_reached = ADVANCE;
			advance_left = 0;
		}
		if (advance_right && !right_end_reached) {
			ret = tree_advance(right_root, right_path, &right_level,
					right_root_level,
					advance_right != ADVANCE_ONLY_NEXT,
					&right_key);
			if (ret < 0)
				right_end_reached = ADVANCE;
			advance_right = 0;
		}

		if (left_end_reached && right_end_reached) {
			ret = 0;
			goto out;
		} else if (left_end_reached) {
			if (right_level == 0) {
				ret = changed_cb(left_root, right_root,
						left_path, right_path,
						&right_key,
						BTRFS_COMPARE_TREE_DELETED,
						ctx);
				if (ret < 0)
					goto out;
			}
			advance_right = ADVANCE;
			continue;
		} else if (right_end_reached) {
			if (left_level == 0) {
				ret = changed_cb(left_root, right_root,
						left_path, right_path,
						&left_key,
						BTRFS_COMPARE_TREE_NEW,
						ctx);
				if (ret < 0)
					goto out;
			}
			advance_left = ADVANCE;
			continue;
		}

		if (left_level == 0 && right_level == 0) {
			cmp = btrfs_comp_cpu_keys(&left_key, &right_key);
			if (cmp < 0) {
				ret = changed_cb(left_root, right_root,
						left_path, right_path,
						&left_key,
						BTRFS_COMPARE_TREE_NEW,
						ctx);
				if (ret < 0)
					goto out;
				advance_left = ADVANCE;
			} else if (cmp > 0) {
				ret = changed_cb(left_root, right_root,
						left_path, right_path,
						&right_key,
						BTRFS_COMPARE_TREE_DELETED,
						ctx);
				if (ret < 0)
					goto out;
				advance_right = ADVANCE;
			} else {
				enum btrfs_compare_tree_result result;

				WARN_ON(!extent_buffer_uptodate(left_path->nodes[0]));
				ret = tree_compare_item(left_root, left_path,
						right_path, tmp_buf);
				if (ret)
					result = BTRFS_COMPARE_TREE_CHANGED;
				else
					result = BTRFS_COMPARE_TREE_SAME;
				ret = changed_cb(left_root, right_root,
						 left_path, right_path,
						 &left_key, result, ctx);
				if (ret < 0)
					goto out;
				advance_left = ADVANCE;
				advance_right = ADVANCE;
			}
		} else if (left_level == right_level) {
			cmp = btrfs_comp_cpu_keys(&left_key, &right_key);
			if (cmp < 0) {
				advance_left = ADVANCE;
			} else if (cmp > 0) {
				advance_right = ADVANCE;
			} else {
				left_blockptr = btrfs_node_blockptr(
						left_path->nodes[left_level],
						left_path->slots[left_level]);
				right_blockptr = btrfs_node_blockptr(
						right_path->nodes[right_level],
						right_path->slots[right_level]);
				left_gen = btrfs_node_ptr_generation(
						left_path->nodes[left_level],
						left_path->slots[left_level]);
				right_gen = btrfs_node_ptr_generation(
						right_path->nodes[right_level],
						right_path->slots[right_level]);
				if (left_blockptr == right_blockptr &&
				    left_gen == right_gen) {
					/*
					 * As we're on a shared block, don't
					 * allow to go deeper.
					 */
					advance_left = ADVANCE_ONLY_NEXT;
					advance_right = ADVANCE_ONLY_NEXT;
				} else {
					advance_left = ADVANCE;
					advance_right = ADVANCE;
				}
			}
		} else if (left_level < right_level) {
			advance_right = ADVANCE;
		} else {
			advance_left = ADVANCE;
		}
	}

out:
	btrfs_free_path(left_path);
	btrfs_free_path(right_path);
	kfree(tmp_buf);
	return ret;
}
