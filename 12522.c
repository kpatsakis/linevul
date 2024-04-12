static int inet_netconf_get_devconf(struct sk_buff *in_skb,
				    struct nlmsghdr *nlh)
{
	struct net *net = sock_net(in_skb->sk);
	struct nlattr *tb[NETCONFA_MAX+1];
	struct netconfmsg *ncm;
	struct sk_buff *skb;
	struct ipv4_devconf *devconf;
	struct in_device *in_dev;
	struct net_device *dev;
	int ifindex;
	int err;

	err = nlmsg_parse(nlh, sizeof(*ncm), tb, NETCONFA_MAX,
			  devconf_ipv4_policy);
	if (err < 0)
		goto errout;

	err = -EINVAL;
	if (!tb[NETCONFA_IFINDEX])
		goto errout;

	ifindex = nla_get_s32(tb[NETCONFA_IFINDEX]);
	switch (ifindex) {
	case NETCONFA_IFINDEX_ALL:
		devconf = net->ipv4.devconf_all;
		break;
	case NETCONFA_IFINDEX_DEFAULT:
		devconf = net->ipv4.devconf_dflt;
		break;
	default:
		dev = __dev_get_by_index(net, ifindex);
		if (!dev)
			goto errout;
		in_dev = __in_dev_get_rtnl(dev);
		if (!in_dev)
			goto errout;
		devconf = &in_dev->cnf;
		break;
	}

	err = -ENOBUFS;
	skb = nlmsg_new(inet_netconf_msgsize_devconf(NETCONFA_ALL), GFP_ATOMIC);
	if (!skb)
		goto errout;

	err = inet_netconf_fill_devconf(skb, ifindex, devconf,
					NETLINK_CB(in_skb).portid,
					nlh->nlmsg_seq, RTM_NEWNETCONF, 0,
					NETCONFA_ALL);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in inet_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout:
	return err;
}
