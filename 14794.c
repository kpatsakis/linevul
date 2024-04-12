static int dcbnl_setall(struct net_device *netdev, struct nlmsghdr *nlh,
			u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	int ret;

	if (!tb[DCB_ATTR_SET_ALL])
		return -EINVAL;

	if (!netdev->dcbnl_ops->setall)
		return -EOPNOTSUPP;

	ret = nla_put_u8(skb, DCB_ATTR_SET_ALL,
			 netdev->dcbnl_ops->setall(netdev));
	dcbnl_cee_notify(netdev, RTM_SETDCB, DCB_CMD_SET_ALL, seq, 0);

	return ret;
}
