static int inet_rtm_deladdr(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tb[IFA_MAX+1];
	struct in_device *in_dev;
	struct ifaddrmsg *ifm;
	struct in_ifaddr *ifa, **ifap;
	int err = -EINVAL;

	ASSERT_RTNL();

	err = nlmsg_parse(nlh, sizeof(*ifm), tb, IFA_MAX, ifa_ipv4_policy);
	if (err < 0)
		goto errout;

	ifm = nlmsg_data(nlh);
	in_dev = inetdev_by_index(net, ifm->ifa_index);
	if (!in_dev) {
		err = -ENODEV;
		goto errout;
	}

	for (ifap = &in_dev->ifa_list; (ifa = *ifap) != NULL;
	     ifap = &ifa->ifa_next) {
		if (tb[IFA_LOCAL] &&
		    ifa->ifa_local != nla_get_in_addr(tb[IFA_LOCAL]))
			continue;

		if (tb[IFA_LABEL] && nla_strcmp(tb[IFA_LABEL], ifa->ifa_label))
			continue;

		if (tb[IFA_ADDRESS] &&
		    (ifm->ifa_prefixlen != ifa->ifa_prefixlen ||
		    !inet_ifa_match(nla_get_in_addr(tb[IFA_ADDRESS]), ifa)))
			continue;

		if (ipv4_is_multicast(ifa->ifa_address))
			ip_mc_config(net->ipv4.mc_autojoin_sk, false, ifa);
		__inet_del_ifa(in_dev, ifap, 1, nlh, NETLINK_CB(skb).portid);
		return 0;
	}

	err = -EADDRNOTAVAIL;
errout:
	return err;
}
