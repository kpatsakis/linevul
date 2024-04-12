static ssize_t sock_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct socket *sock = file->private_data;
	struct msghdr msg = {.msg_iter = *from};
	ssize_t res;

	if (iocb->ki_pos != 0)
		return -ESPIPE;

	if (file->f_flags & O_NONBLOCK)
		msg.msg_flags = MSG_DONTWAIT;

	if (sock->type == SOCK_SEQPACKET)
		msg.msg_flags |= MSG_EOR;

	res = __sock_sendmsg(iocb, sock, &msg, iocb->ki_nbytes);
	*from = msg.msg_iter;
	return res;
}
