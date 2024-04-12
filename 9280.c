static int proc_keys_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &proc_keys_ops);
}
