static void ext4_handle_error(struct super_block *sb)
{
	struct ext4_super_block *es = EXT4_SB(sb)->s_es;

	EXT4_SB(sb)->s_mount_state |= EXT4_ERROR_FS;
	es->s_state |= cpu_to_le16(EXT4_ERROR_FS);

	if (sb->s_flags & MS_RDONLY)
		return;

	if (!test_opt(sb, ERRORS_CONT)) {
		journal_t *journal = EXT4_SB(sb)->s_journal;

		EXT4_SB(sb)->s_mount_flags |= EXT4_MF_FS_ABORTED;
		if (journal)
			jbd2_journal_abort(journal, -EIO);
	}
	if (test_opt(sb, ERRORS_RO)) {
		ext4_msg(sb, KERN_CRIT, "Remounting filesystem read-only");
		sb->s_flags |= MS_RDONLY;
	}
	ext4_commit_super(sb, 1);
	if (test_opt(sb, ERRORS_PANIC))
		panic("EXT4-fs (device %s): panic forced after error\n",
			sb->s_id);
}
