static int ctrl_fill_mcgrp_info(const struct genl_family *family,
				const struct genl_multicast_group *grp,
				int grp_id, u32 portid, u32 seq, u32 flags,
				struct sk_buff *skb, u8 cmd)
{
	void *hdr;
	struct nlattr *nla_grps;
	struct nlattr *nest;

	hdr = genlmsg_put(skb, portid, seq, &genl_ctrl, flags, cmd);
	if (hdr == NULL)
		return -1;

	if (nla_put_string(skb, CTRL_ATTR_FAMILY_NAME, family->name) ||
	    nla_put_u16(skb, CTRL_ATTR_FAMILY_ID, family->id))
		goto nla_put_failure;

	nla_grps = nla_nest_start(skb, CTRL_ATTR_MCAST_GROUPS);
	if (nla_grps == NULL)
		goto nla_put_failure;

	nest = nla_nest_start(skb, 1);
	if (nest == NULL)
		goto nla_put_failure;

	if (nla_put_u32(skb, CTRL_ATTR_MCAST_GRP_ID, grp_id) ||
	    nla_put_string(skb, CTRL_ATTR_MCAST_GRP_NAME,
			   grp->name))
		goto nla_put_failure;

	nla_nest_end(skb, nest);
	nla_nest_end(skb, nla_grps);

	genlmsg_end(skb, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	return -EMSGSIZE;
}
