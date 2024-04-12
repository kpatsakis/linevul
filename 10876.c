int btrfs_add_dead_root(struct btrfs_root *root)
{
	spin_lock(&root->fs_info->trans_lock);
	list_add(&root->root_list, &root->fs_info->dead_roots);
	spin_unlock(&root->fs_info->trans_lock);
	return 0;
}
