static inline struct sock *l2tp_ip_bind_lookup(struct net *net, __be32 laddr, int dif, u32 tunnel_id)
{
	struct sock *sk = __l2tp_ip_bind_lookup(net, laddr, dif, tunnel_id);
	if (sk)
		sock_hold(sk);

	return sk;
}
