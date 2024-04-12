static inline int netlink_is_kernel(struct sock *sk)
{
	return nlk_sk(sk)->flags & NETLINK_KERNEL_SOCKET;
}
