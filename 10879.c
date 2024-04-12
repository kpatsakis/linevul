static int write_end_fn(handle_t *handle, struct buffer_head *bh)
{
	int ret;
	if (!buffer_mapped(bh) || buffer_freed(bh))
		return 0;
	set_buffer_uptodate(bh);
	ret = ext4_handle_dirty_metadata(handle, NULL, bh);
	clear_buffer_meta(bh);
	clear_buffer_prio(bh);
	return ret;
}
