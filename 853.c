static int pppol2tp_proc_open(struct inode *inode, struct file *file)
{
	return seq_open_net(inode, file, &pppol2tp_seq_ops,
			    sizeof(struct pppol2tp_seq_data));
}
