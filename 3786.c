static int dcbnl_pgtx_setcfg(struct net_device *netdev, struct nlmsghdr *nlh,
			     u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	return __dcbnl_pg_setcfg(netdev, nlh, seq, tb, skb, 0);
}
