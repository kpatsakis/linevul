static int dn_setsockopt(struct socket *sock, int level, int optname, char __user *optval, unsigned int optlen)
{
	struct sock *sk = sock->sk;
	int err;

	lock_sock(sk);
	err = __dn_setsockopt(sock, level, optname, optval, optlen, 0);
	release_sock(sk);

	return err;
}
