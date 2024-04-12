static int sock_sendmsg_nosec(struct socket *sock, struct msghdr *msg, size_t size)
{
	return do_sock_sendmsg(sock, msg, size, true);
}
