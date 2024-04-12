static ssize_t macvtap_aio_write(struct kiocb *iocb, const struct iovec *iv,
				 unsigned long count, loff_t pos)
{
	struct file *file = iocb->ki_filp;
	ssize_t result = -ENOLINK;
	struct macvtap_queue *q = file->private_data;

	result = macvtap_get_user(q, NULL, iv, iov_length(iv, count), count,
				  file->f_flags & O_NONBLOCK);
	return result;
}
