static ssize_t fuse_dev_splice_read(struct file *in, loff_t *ppos,
				    struct pipe_inode_info *pipe,
				    size_t len, unsigned int flags)
{
	int total, ret;
	int page_nr = 0;
	struct pipe_buffer *bufs;
	struct fuse_copy_state cs;
	struct fuse_dev *fud = fuse_get_dev(in);

	if (!fud)
		return -EPERM;

	bufs = kvmalloc_array(pipe->buffers, sizeof(struct pipe_buffer),
			      GFP_KERNEL);
	if (!bufs)
		return -ENOMEM;

	fuse_copy_init(&cs, 1, NULL);
	cs.pipebufs = bufs;
	cs.pipe = pipe;
	ret = fuse_dev_do_read(fud, in, &cs, len);
	if (ret < 0)
		goto out;

	if (pipe->nrbufs + cs.nr_segs > pipe->buffers) {
		ret = -EIO;
		goto out;
	}

	for (ret = total = 0; page_nr < cs.nr_segs; total += ret) {
		/*
		 * Need to be careful about this.  Having buf->ops in module
		 * code can Oops if the buffer persists after module unload.
		 */
		bufs[page_nr].ops = &nosteal_pipe_buf_ops;
		bufs[page_nr].flags = 0;
		ret = add_to_pipe(pipe, &bufs[page_nr++]);
		if (unlikely(ret < 0))
			break;
	}
	if (total)
		ret = total;
out:
	for (; page_nr < cs.nr_segs; page_nr++)
		put_page(bufs[page_nr].page);

	kvfree(bufs);
	return ret;
}
