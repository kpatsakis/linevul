static int inet_rtm_getroute(struct sk_buff *in_skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	struct nlattr *tb[RTA_MAX+1];
	u32 table_id = RT_TABLE_MAIN;
	__be16 sport = 0, dport = 0;
	struct fib_result res = {};
	u8 ip_proto = IPPROTO_UDP;
	struct rtable *rt = NULL;
	struct sk_buff *skb;
	struct rtmsg *rtm;
	struct flowi4 fl4 = {};
	__be32 dst = 0;
	__be32 src = 0;
	kuid_t uid;
	u32 iif;
	int err;
	int mark;

	err = inet_rtm_valid_getroute_req(in_skb, nlh, tb, extack);
	if (err < 0)
		return err;

	rtm = nlmsg_data(nlh);
	src = tb[RTA_SRC] ? nla_get_in_addr(tb[RTA_SRC]) : 0;
	dst = tb[RTA_DST] ? nla_get_in_addr(tb[RTA_DST]) : 0;
	iif = tb[RTA_IIF] ? nla_get_u32(tb[RTA_IIF]) : 0;
	mark = tb[RTA_MARK] ? nla_get_u32(tb[RTA_MARK]) : 0;
	if (tb[RTA_UID])
		uid = make_kuid(current_user_ns(), nla_get_u32(tb[RTA_UID]));
	else
		uid = (iif ? INVALID_UID : current_uid());

	if (tb[RTA_IP_PROTO]) {
		err = rtm_getroute_parse_ip_proto(tb[RTA_IP_PROTO],
						  &ip_proto, AF_INET, extack);
		if (err)
			return err;
	}

	if (tb[RTA_SPORT])
		sport = nla_get_be16(tb[RTA_SPORT]);

	if (tb[RTA_DPORT])
		dport = nla_get_be16(tb[RTA_DPORT]);

	skb = inet_rtm_getroute_build_skb(src, dst, ip_proto, sport, dport);
	if (!skb)
		return -ENOBUFS;

	fl4.daddr = dst;
	fl4.saddr = src;
	fl4.flowi4_tos = rtm->rtm_tos;
	fl4.flowi4_oif = tb[RTA_OIF] ? nla_get_u32(tb[RTA_OIF]) : 0;
	fl4.flowi4_mark = mark;
	fl4.flowi4_uid = uid;
	if (sport)
		fl4.fl4_sport = sport;
	if (dport)
		fl4.fl4_dport = dport;
	fl4.flowi4_proto = ip_proto;

	rcu_read_lock();

	if (iif) {
		struct net_device *dev;

		dev = dev_get_by_index_rcu(net, iif);
		if (!dev) {
			err = -ENODEV;
			goto errout_rcu;
		}

		fl4.flowi4_iif = iif; /* for rt_fill_info */
		skb->dev	= dev;
		skb->mark	= mark;
		err = ip_route_input_rcu(skb, dst, src, rtm->rtm_tos,
					 dev, &res);

		rt = skb_rtable(skb);
		if (err == 0 && rt->dst.error)
			err = -rt->dst.error;
	} else {
		fl4.flowi4_iif = LOOPBACK_IFINDEX;
		skb->dev = net->loopback_dev;
		rt = ip_route_output_key_hash_rcu(net, &fl4, &res, skb);
		err = 0;
		if (IS_ERR(rt))
			err = PTR_ERR(rt);
		else
			skb_dst_set(skb, &rt->dst);
	}

	if (err)
		goto errout_rcu;

	if (rtm->rtm_flags & RTM_F_NOTIFY)
		rt->rt_flags |= RTCF_NOTIFY;

	if (rtm->rtm_flags & RTM_F_LOOKUP_TABLE)
		table_id = res.table ? res.table->tb_id : 0;

	/* reset skb for netlink reply msg */
	skb_trim(skb, 0);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb_reset_mac_header(skb);

	if (rtm->rtm_flags & RTM_F_FIB_MATCH) {
		if (!res.fi) {
			err = fib_props[res.type].error;
			if (!err)
				err = -EHOSTUNREACH;
			goto errout_rcu;
		}
		err = fib_dump_info(skb, NETLINK_CB(in_skb).portid,
				    nlh->nlmsg_seq, RTM_NEWROUTE, table_id,
				    rt->rt_type, res.prefix, res.prefixlen,
				    fl4.flowi4_tos, res.fi, 0);
	} else {
		err = rt_fill_info(net, dst, src, rt, table_id, &fl4, skb,
				   NETLINK_CB(in_skb).portid, nlh->nlmsg_seq);
	}
	if (err < 0)
		goto errout_rcu;

	rcu_read_unlock();

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);

errout_free:
	return err;
errout_rcu:
	rcu_read_unlock();
	kfree_skb(skb);
	goto errout_free;
}
