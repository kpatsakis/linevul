static int proc_key_users_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &proc_key_users_ops);
}
