static int qib_open(struct inode *in, struct file *fp)
{
	/* The real work is performed later in qib_assign_ctxt() */
	fp->private_data = kzalloc(sizeof(struct qib_filedata), GFP_KERNEL);
	if (fp->private_data) /* no cpu affinity by default */
		((struct qib_filedata *)fp->private_data)->rec_cpu_num = -1;
	return fp->private_data ? 0 : -ENOMEM;
}
