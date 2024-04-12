int ext4_force_commit(struct super_block *sb)
{
	journal_t *journal;

	if (sb->s_flags & MS_RDONLY)
		return 0;

	journal = EXT4_SB(sb)->s_journal;
	return ext4_journal_force_commit(journal);
}
