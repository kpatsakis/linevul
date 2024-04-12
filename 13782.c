static int dn_getsockopt(struct socket *sock, int level, int optname, char __user *optval, int __user *optlen)
{
	struct sock *sk = sock->sk;
	int err;

	lock_sock(sk);
	err = __dn_getsockopt(sock, level, optname, optval, optlen, 0);
	release_sock(sk);

	return err;
}
