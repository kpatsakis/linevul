static int inet_rtm_getroute(struct sk_buff *in_skb, struct nlmsghdr *nlh)
{
	struct net *net = sock_net(in_skb->sk);
	struct rtmsg *rtm;
	struct nlattr *tb[RTA_MAX+1];
	struct rtable *rt = NULL;
	struct flowi4 fl4;
	__be32 dst = 0;
	__be32 src = 0;
	u32 iif;
	int err;
	int mark;
	struct sk_buff *skb;

	err = nlmsg_parse(nlh, sizeof(*rtm), tb, RTA_MAX, rtm_ipv4_policy);
	if (err < 0)
		goto errout;

	rtm = nlmsg_data(nlh);

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (skb == NULL) {
		err = -ENOBUFS;
		goto errout;
	}

	/* Reserve room for dummy headers, this skb can pass
	   through good chunk of routing engine.
	 */
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);

	/* Bugfix: need to give ip_route_input enough of an IP header to not gag. */
	ip_hdr(skb)->protocol = IPPROTO_ICMP;
	skb_reserve(skb, MAX_HEADER + sizeof(struct iphdr));

	src = tb[RTA_SRC] ? nla_get_be32(tb[RTA_SRC]) : 0;
	dst = tb[RTA_DST] ? nla_get_be32(tb[RTA_DST]) : 0;
	iif = tb[RTA_IIF] ? nla_get_u32(tb[RTA_IIF]) : 0;
	mark = tb[RTA_MARK] ? nla_get_u32(tb[RTA_MARK]) : 0;

	memset(&fl4, 0, sizeof(fl4));
	fl4.daddr = dst;
	fl4.saddr = src;
	fl4.flowi4_tos = rtm->rtm_tos;
	fl4.flowi4_oif = tb[RTA_OIF] ? nla_get_u32(tb[RTA_OIF]) : 0;
	fl4.flowi4_mark = mark;

	if (iif) {
		struct net_device *dev;

		dev = __dev_get_by_index(net, iif);
		if (dev == NULL) {
			err = -ENODEV;
			goto errout_free;
		}

		skb->protocol	= htons(ETH_P_IP);
		skb->dev	= dev;
		skb->mark	= mark;
		local_bh_disable();
		err = ip_route_input(skb, dst, src, rtm->rtm_tos, dev);
		local_bh_enable();

		rt = skb_rtable(skb);
		if (err == 0 && rt->dst.error)
			err = -rt->dst.error;
	} else {
		rt = ip_route_output_key(net, &fl4);

		err = 0;
		if (IS_ERR(rt))
			err = PTR_ERR(rt);
	}

	if (err)
		goto errout_free;

	skb_dst_set(skb, &rt->dst);
	if (rtm->rtm_flags & RTM_F_NOTIFY)
		rt->rt_flags |= RTCF_NOTIFY;

	err = rt_fill_info(net, dst, src, &fl4, skb,
			   NETLINK_CB(in_skb).portid, nlh->nlmsg_seq,
			   RTM_NEWROUTE, 0, 0);
	if (err <= 0)
		goto errout_free;

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout:
	return err;

errout_free:
	kfree_skb(skb);
	goto errout;
}
