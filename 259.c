static long vmsplice_to_pipe(struct file *file, struct iov_iter *iter,
			     unsigned int flags)
{
	struct pipe_inode_info *pipe;
	long ret = 0;
	unsigned buf_flag = 0;

	if (flags & SPLICE_F_GIFT)
		buf_flag = PIPE_BUF_FLAG_GIFT;

	pipe = get_pipe_info(file);
	if (!pipe)
		return -EBADF;

	pipe_lock(pipe);
	ret = wait_for_space(pipe, flags);
	if (!ret)
		ret = iter_to_pipe(iter, pipe, buf_flag);
	pipe_unlock(pipe);
	if (ret > 0)
		wakeup_pipe_readers(pipe);
	return ret;
}
