struct sock *mroute6_socket(struct net *net, struct sk_buff *skb)
{
	struct mr6_table *mrt;
	struct flowi6 fl6 = {
		.flowi6_iif	= skb->skb_iif ? : LOOPBACK_IFINDEX,
		.flowi6_oif	= skb->dev->ifindex,
		.flowi6_mark	= skb->mark,
	};

	if (ip6mr_fib_lookup(net, &fl6, &mrt) < 0)
		return NULL;

	return mrt->mroute6_sk;
}
