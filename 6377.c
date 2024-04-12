int btrfs_clean_old_snapshots(struct btrfs_root *root)
{
	LIST_HEAD(list);
	struct btrfs_fs_info *fs_info = root->fs_info;

	spin_lock(&fs_info->trans_lock);
	list_splice_init(&fs_info->dead_roots, &list);
	spin_unlock(&fs_info->trans_lock);

	while (!list_empty(&list)) {
		int ret;

		root = list_entry(list.next, struct btrfs_root, root_list);
		list_del(&root->root_list);

		btrfs_kill_all_delayed_nodes(root);

		if (btrfs_header_backref_rev(root->node) <
		    BTRFS_MIXED_BACKREF_REV)
			ret = btrfs_drop_snapshot(root, NULL, 0, 0);
		else
			ret =btrfs_drop_snapshot(root, NULL, 1, 0);
		BUG_ON(ret < 0);
	}
	return 0;
}
