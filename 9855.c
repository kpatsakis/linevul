static int bpf_fill_super(struct super_block *sb, void *data, int silent)
{
	static struct tree_descr bpf_rfiles[] = { { "" } };
	struct inode *inode;
	int ret;

	ret = simple_fill_super(sb, BPF_FS_MAGIC, bpf_rfiles);
	if (ret)
		return ret;

	sb->s_op = &bpf_super_ops;

	inode = sb->s_root->d_inode;
	inode->i_op = &bpf_dir_iops;
	inode->i_mode &= ~S_IALLUGO;
	inode->i_mode |= S_ISVTX | S_IRWXUGO;

	return 0;
}
