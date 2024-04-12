static int cmd_attr_tgid(struct genl_info *info)
{
	struct taskstats *stats;
	struct sk_buff *rep_skb;
	size_t size;
	u32 tgid;
	int rc;

	size = taskstats_packet_size();

	rc = prepare_reply(info, TASKSTATS_CMD_NEW, &rep_skb, size);
	if (rc < 0)
		return rc;

	rc = -EINVAL;
	tgid = nla_get_u32(info->attrs[TASKSTATS_CMD_ATTR_TGID]);
	stats = mk_reply(rep_skb, TASKSTATS_TYPE_TGID, tgid);
	if (!stats)
		goto err;

	rc = fill_stats_for_tgid(tgid, stats);
	if (rc < 0)
		goto err;
	return send_reply(rep_skb, info);
err:
	nlmsg_free(rep_skb);
	return rc;
}
