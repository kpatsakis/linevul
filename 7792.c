static inline void ext4_show_quota_options(struct seq_file *seq,
					   struct super_block *sb)
{
#if defined(CONFIG_QUOTA)
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	if (sbi->s_jquota_fmt) {
		char *fmtname = "";

		switch (sbi->s_jquota_fmt) {
		case QFMT_VFS_OLD:
			fmtname = "vfsold";
			break;
		case QFMT_VFS_V0:
			fmtname = "vfsv0";
			break;
		case QFMT_VFS_V1:
			fmtname = "vfsv1";
			break;
		}
		seq_printf(seq, ",jqfmt=%s", fmtname);
	}

	if (sbi->s_qf_names[USRQUOTA])
		seq_show_option(seq, "usrjquota", sbi->s_qf_names[USRQUOTA]);

	if (sbi->s_qf_names[GRPQUOTA])
		seq_show_option(seq, "grpjquota", sbi->s_qf_names[GRPQUOTA]);
#endif
}
