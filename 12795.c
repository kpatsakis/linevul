static int ip6mr_fill_mroute(struct mr6_table *mrt, struct sk_buff *skb,
			     u32 portid, u32 seq, struct mfc6_cache *c, int cmd,
			     int flags)
{
	struct nlmsghdr *nlh;
	struct rtmsg *rtm;
	int err;

	nlh = nlmsg_put(skb, portid, seq, cmd, sizeof(*rtm), flags);
	if (!nlh)
		return -EMSGSIZE;

	rtm = nlmsg_data(nlh);
	rtm->rtm_family   = RTNL_FAMILY_IP6MR;
	rtm->rtm_dst_len  = 128;
	rtm->rtm_src_len  = 128;
	rtm->rtm_tos      = 0;
	rtm->rtm_table    = mrt->id;
	if (nla_put_u32(skb, RTA_TABLE, mrt->id))
		goto nla_put_failure;
	rtm->rtm_type = RTN_MULTICAST;
	rtm->rtm_scope    = RT_SCOPE_UNIVERSE;
	if (c->mfc_flags & MFC_STATIC)
		rtm->rtm_protocol = RTPROT_STATIC;
	else
		rtm->rtm_protocol = RTPROT_MROUTED;
	rtm->rtm_flags    = 0;

	if (nla_put_in6_addr(skb, RTA_SRC, &c->mf6c_origin) ||
	    nla_put_in6_addr(skb, RTA_DST, &c->mf6c_mcastgrp))
		goto nla_put_failure;
	err = __ip6mr_fill_mroute(mrt, skb, c, rtm);
	/* do not break the dump if cache is unresolved */
	if (err < 0 && err != -ENOENT)
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}
