static void ext3_orphan_cleanup (struct super_block * sb,
				 struct ext3_super_block * es)
{
	unsigned int s_flags = sb->s_flags;
	int nr_orphans = 0, nr_truncates = 0;
#ifdef CONFIG_QUOTA
	int i;
#endif
	if (!es->s_last_orphan) {
		jbd_debug(4, "no orphan inodes to clean up\n");
		return;
	}

	if (bdev_read_only(sb->s_bdev)) {
		ext3_msg(sb, KERN_ERR, "error: write access "
			"unavailable, skipping orphan cleanup.");
		return;
	}

	/* Check if feature set allows readwrite operations */
	if (EXT3_HAS_RO_COMPAT_FEATURE(sb, ~EXT3_FEATURE_RO_COMPAT_SUPP)) {
		ext3_msg(sb, KERN_INFO, "Skipping orphan cleanup due to "
			 "unknown ROCOMPAT features");
		return;
	}

	if (EXT3_SB(sb)->s_mount_state & EXT3_ERROR_FS) {
		/* don't clear list on RO mount w/ errors */
		if (es->s_last_orphan && !(s_flags & MS_RDONLY)) {
			jbd_debug(1, "Errors on filesystem, "
				  "clearing orphan list.\n");
			es->s_last_orphan = 0;
		}
		jbd_debug(1, "Skipping orphan recovery on fs with errors.\n");
		return;
	}

	if (s_flags & MS_RDONLY) {
		ext3_msg(sb, KERN_INFO, "orphan cleanup on readonly fs");
		sb->s_flags &= ~MS_RDONLY;
	}
#ifdef CONFIG_QUOTA
	/* Needed for iput() to work correctly and not trash data */
	sb->s_flags |= MS_ACTIVE;
	/* Turn on quotas so that they are updated correctly */
	for (i = 0; i < MAXQUOTAS; i++) {
		if (EXT3_SB(sb)->s_qf_names[i]) {
			int ret = ext3_quota_on_mount(sb, i);
			if (ret < 0)
				ext3_msg(sb, KERN_ERR,
					"error: cannot turn on journaled "
					"quota: %d", ret);
		}
	}
#endif

	while (es->s_last_orphan) {
		struct inode *inode;

		inode = ext3_orphan_get(sb, le32_to_cpu(es->s_last_orphan));
		if (IS_ERR(inode)) {
			es->s_last_orphan = 0;
			break;
		}

		list_add(&EXT3_I(inode)->i_orphan, &EXT3_SB(sb)->s_orphan);
		dquot_initialize(inode);
		if (inode->i_nlink) {
			printk(KERN_DEBUG
				"%s: truncating inode %lu to %Ld bytes\n",
				__func__, inode->i_ino, inode->i_size);
			jbd_debug(2, "truncating inode %lu to %Ld bytes\n",
				  inode->i_ino, inode->i_size);
			ext3_truncate(inode);
			nr_truncates++;
		} else {
			printk(KERN_DEBUG
				"%s: deleting unreferenced inode %lu\n",
				__func__, inode->i_ino);
			jbd_debug(2, "deleting unreferenced inode %lu\n",
				  inode->i_ino);
			nr_orphans++;
		}
		iput(inode);  /* The delete magic happens here! */
	}

#define PLURAL(x) (x), ((x)==1) ? "" : "s"

	if (nr_orphans)
		ext3_msg(sb, KERN_INFO, "%d orphan inode%s deleted",
		       PLURAL(nr_orphans));
	if (nr_truncates)
		ext3_msg(sb, KERN_INFO, "%d truncate%s cleaned up",
		       PLURAL(nr_truncates));
#ifdef CONFIG_QUOTA
	/* Turn quotas off */
	for (i = 0; i < MAXQUOTAS; i++) {
		if (sb_dqopt(sb)->files[i])
			dquot_quota_off(sb, i);
	}
#endif
	sb->s_flags = s_flags; /* Restore MS_RDONLY status */
}
