nlmsvc_remove_block(struct nlm_block *block)
{
	if (!list_empty(&block->b_list)) {
		spin_lock(&nlm_blocked_lock);
		list_del_init(&block->b_list);
		spin_unlock(&nlm_blocked_lock);
		nlmsvc_release_block(block);
	}
}
