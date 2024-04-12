static void trace_packet(struct net *net,
			 const struct sk_buff *skb,
			 unsigned int hook,
			 const struct net_device *in,
			 const struct net_device *out,
			 const char *tablename,
			 const struct xt_table_info *private,
			 const struct ip6t_entry *e)
{
	const struct ip6t_entry *root;
	const char *hookname, *chainname, *comment;
	const struct ip6t_entry *iter;
	unsigned int rulenum = 0;

	root = get_entry(private->entries, private->hook_entry[hook]);

	hookname = chainname = hooknames[hook];
	comment = comments[NF_IP6_TRACE_COMMENT_RULE];

	xt_entry_foreach(iter, root, private->size - private->hook_entry[hook])
		if (get_chainname_rulenum(iter, e, hookname,
		    &chainname, &comment, &rulenum) != 0)
			break;

	nf_log_trace(net, AF_INET6, hook, skb, in, out, &trace_loginfo,
		     "TRACE: %s:%s:%s:%u ",
		     tablename, chainname, comment, rulenum);
}
