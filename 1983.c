static inline struct netlink_sock *nlk_sk(struct sock *sk)
{
	return container_of(sk, struct netlink_sock, sk);
}
