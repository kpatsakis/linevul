static inline void tree_mod_log_write_unlock(struct btrfs_fs_info *fs_info)
{
	write_unlock(&fs_info->tree_mod_log_lock);
}
