arpt_error(struct sk_buff *skb, const struct xt_action_param *par)
{
	net_err_ratelimited("arp_tables: error: '%s'\n",
			    (const char *)par->targinfo);

	return NF_DROP;
}
