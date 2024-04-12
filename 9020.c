static bool ipv6_dest_hao(struct sk_buff *skb, int optoff)
{
	struct ipv6_destopt_hao *hao;
	struct inet6_skb_parm *opt = IP6CB(skb);
	struct ipv6hdr *ipv6h = ipv6_hdr(skb);
	struct in6_addr tmp_addr;
	int ret;

	if (opt->dsthao) {
		net_dbg_ratelimited("hao duplicated\n");
		goto discard;
	}
	opt->dsthao = opt->dst1;
	opt->dst1 = 0;

	hao = (struct ipv6_destopt_hao *)(skb_network_header(skb) + optoff);

	if (hao->length != 16) {
		net_dbg_ratelimited("hao invalid option length = %d\n",
				    hao->length);
		goto discard;
	}

	if (!(ipv6_addr_type(&hao->addr) & IPV6_ADDR_UNICAST)) {
		net_dbg_ratelimited("hao is not an unicast addr: %pI6\n",
				    &hao->addr);
		goto discard;
	}

	ret = xfrm6_input_addr(skb, (xfrm_address_t *)&ipv6h->daddr,
			       (xfrm_address_t *)&hao->addr, IPPROTO_DSTOPTS);
	if (unlikely(ret < 0))
		goto discard;

	if (skb_cloned(skb)) {
		if (pskb_expand_head(skb, 0, 0, GFP_ATOMIC))
			goto discard;

		/* update all variable using below by copied skbuff */
		hao = (struct ipv6_destopt_hao *)(skb_network_header(skb) +
						  optoff);
		ipv6h = ipv6_hdr(skb);
	}

	if (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;

	tmp_addr = ipv6h->saddr;
	ipv6h->saddr = hao->addr;
	hao->addr = tmp_addr;

	if (skb->tstamp.tv64 == 0)
		__net_timestamp(skb);

	return true;

 discard:
	kfree_skb(skb);
	return false;
}
