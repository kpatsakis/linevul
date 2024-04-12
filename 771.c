static void rtmsg_ifa(int event, struct in_ifaddr *ifa, struct nlmsghdr *nlh,
		      u32 portid)
{
	struct sk_buff *skb;
	u32 seq = nlh ? nlh->nlmsg_seq : 0;
	int err = -ENOBUFS;
	struct net *net;

	net = dev_net(ifa->ifa_dev->dev);
	skb = nlmsg_new(inet_nlmsg_size(), GFP_KERNEL);
	if (!skb)
		goto errout;

	err = inet_fill_ifaddr(skb, ifa, portid, seq, event, 0);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in inet_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	rtnl_notify(skb, net, portid, RTNLGRP_IPV4_IFADDR, nlh, GFP_KERNEL);
	return;
errout:
	if (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV4_IFADDR, err);
}
