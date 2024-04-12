static int f2fs_remount(struct super_block *sb, int *flags, char *data)
{
	struct f2fs_sb_info *sbi = F2FS_SB(sb);
	struct f2fs_mount_info org_mount_opt;
	unsigned long old_sb_flags;
	int err, active_logs;
	bool need_restart_gc = false;
	bool need_stop_gc = false;
	bool no_extent_cache = !test_opt(sbi, EXTENT_CACHE);
#ifdef CONFIG_F2FS_FAULT_INJECTION
	struct f2fs_fault_info ffi = sbi->fault_info;
#endif
#ifdef CONFIG_QUOTA
	int s_jquota_fmt;
	char *s_qf_names[MAXQUOTAS];
	int i, j;
#endif

	/*
	 * Save the old mount options in case we
	 * need to restore them.
	 */
	org_mount_opt = sbi->mount_opt;
	old_sb_flags = sb->s_flags;
	active_logs = sbi->active_logs;

#ifdef CONFIG_QUOTA
	s_jquota_fmt = sbi->s_jquota_fmt;
	for (i = 0; i < MAXQUOTAS; i++) {
		if (sbi->s_qf_names[i]) {
			s_qf_names[i] = kstrdup(sbi->s_qf_names[i],
							 GFP_KERNEL);
			if (!s_qf_names[i]) {
				for (j = 0; j < i; j++)
					kfree(s_qf_names[j]);
				return -ENOMEM;
			}
		} else {
			s_qf_names[i] = NULL;
		}
	}
#endif

	/* recover superblocks we couldn't write due to previous RO mount */
	if (!(*flags & MS_RDONLY) && is_sbi_flag_set(sbi, SBI_NEED_SB_WRITE)) {
		err = f2fs_commit_super(sbi, false);
		f2fs_msg(sb, KERN_INFO,
			"Try to recover all the superblocks, ret: %d", err);
		if (!err)
			clear_sbi_flag(sbi, SBI_NEED_SB_WRITE);
	}

	default_options(sbi);

	/* parse mount options */
	err = parse_options(sb, data);
	if (err)
		goto restore_opts;

	/*
	 * Previous and new state of filesystem is RO,
	 * so skip checking GC and FLUSH_MERGE conditions.
	 */
	if (f2fs_readonly(sb) && (*flags & MS_RDONLY))
		goto skip;

	if (!f2fs_readonly(sb) && (*flags & MS_RDONLY)) {
		err = dquot_suspend(sb, -1);
		if (err < 0)
			goto restore_opts;
	} else {
		/* dquot_resume needs RW */
		sb->s_flags &= ~MS_RDONLY;
		dquot_resume(sb, -1);
	}

	/* disallow enable/disable extent_cache dynamically */
	if (no_extent_cache == !!test_opt(sbi, EXTENT_CACHE)) {
		err = -EINVAL;
		f2fs_msg(sbi->sb, KERN_WARNING,
				"switch extent_cache option is not allowed");
		goto restore_opts;
	}

	/*
	 * We stop the GC thread if FS is mounted as RO
	 * or if background_gc = off is passed in mount
	 * option. Also sync the filesystem.
	 */
	if ((*flags & MS_RDONLY) || !test_opt(sbi, BG_GC)) {
		if (sbi->gc_thread) {
			stop_gc_thread(sbi);
			need_restart_gc = true;
		}
	} else if (!sbi->gc_thread) {
		err = start_gc_thread(sbi);
		if (err)
			goto restore_opts;
		need_stop_gc = true;
	}

	if (*flags & MS_RDONLY) {
		writeback_inodes_sb(sb, WB_REASON_SYNC);
		sync_inodes_sb(sb);

		set_sbi_flag(sbi, SBI_IS_DIRTY);
		set_sbi_flag(sbi, SBI_IS_CLOSE);
		f2fs_sync_fs(sb, 1);
		clear_sbi_flag(sbi, SBI_IS_CLOSE);
	}

	/*
	 * We stop issue flush thread if FS is mounted as RO
	 * or if flush_merge is not passed in mount option.
	 */
	if ((*flags & MS_RDONLY) || !test_opt(sbi, FLUSH_MERGE)) {
		clear_opt(sbi, FLUSH_MERGE);
		destroy_flush_cmd_control(sbi, false);
	} else {
		err = create_flush_cmd_control(sbi);
		if (err)
			goto restore_gc;
	}
skip:
#ifdef CONFIG_QUOTA
	/* Release old quota file names */
	for (i = 0; i < MAXQUOTAS; i++)
		kfree(s_qf_names[i]);
#endif
	/* Update the POSIXACL Flag */
	sb->s_flags = (sb->s_flags & ~MS_POSIXACL) |
		(test_opt(sbi, POSIX_ACL) ? MS_POSIXACL : 0);

	return 0;
restore_gc:
	if (need_restart_gc) {
		if (start_gc_thread(sbi))
			f2fs_msg(sbi->sb, KERN_WARNING,
				"background gc thread has stopped");
	} else if (need_stop_gc) {
		stop_gc_thread(sbi);
	}
restore_opts:
#ifdef CONFIG_QUOTA
	sbi->s_jquota_fmt = s_jquota_fmt;
	for (i = 0; i < MAXQUOTAS; i++) {
		kfree(sbi->s_qf_names[i]);
		sbi->s_qf_names[i] = s_qf_names[i];
	}
#endif
	sbi->mount_opt = org_mount_opt;
	sbi->active_logs = active_logs;
	sb->s_flags = old_sb_flags;
#ifdef CONFIG_F2FS_FAULT_INJECTION
	sbi->fault_info = ffi;
#endif
	return err;
}
