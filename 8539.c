static int ext3_sync_fs(struct super_block *sb, int wait)
{
	tid_t target;

	trace_ext3_sync_fs(sb, wait);
	/*
	 * Writeback quota in non-journalled quota case - journalled quota has
	 * no dirty dquots
	 */
	dquot_writeback_dquots(sb, -1);
	if (journal_start_commit(EXT3_SB(sb)->s_journal, &target)) {
		if (wait)
			log_wait_commit(EXT3_SB(sb)->s_journal, target);
	}
	return 0;
}
