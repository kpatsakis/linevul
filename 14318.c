static void tree_move_down(struct btrfs_root *root,
			   struct btrfs_path *path,
			   int *level, int root_level)
{
	BUG_ON(*level == 0);
	path->nodes[*level - 1] = read_node_slot(root, path->nodes[*level],
					path->slots[*level]);
	path->slots[*level - 1] = 0;
	(*level)--;
}
