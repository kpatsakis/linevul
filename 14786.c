static int dcbnl_getstate(struct net_device *netdev, struct nlmsghdr *nlh,
			  u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	/* if (!tb[DCB_ATTR_STATE] || !netdev->dcbnl_ops->getstate) */
	if (!netdev->dcbnl_ops->getstate)
		return -EOPNOTSUPP;

	return nla_put_u8(skb, DCB_ATTR_STATE,
			  netdev->dcbnl_ops->getstate(netdev));
}
