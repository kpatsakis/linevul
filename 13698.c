static struct sk_buff *inet_rtm_getroute_build_skb(__be32 src, __be32 dst,
						   u8 ip_proto, __be16 sport,
						   __be16 dport)
{
	struct sk_buff *skb;
	struct iphdr *iph;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb)
		return NULL;

	/* Reserve room for dummy headers, this skb can pass
	 * through good chunk of routing engine.
	 */
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb->protocol = htons(ETH_P_IP);
	iph = skb_put(skb, sizeof(struct iphdr));
	iph->protocol = ip_proto;
	iph->saddr = src;
	iph->daddr = dst;
	iph->version = 0x4;
	iph->frag_off = 0;
	iph->ihl = 0x5;
	skb_set_transport_header(skb, skb->len);

	switch (iph->protocol) {
	case IPPROTO_UDP: {
		struct udphdr *udph;

		udph = skb_put_zero(skb, sizeof(struct udphdr));
		udph->source = sport;
		udph->dest = dport;
		udph->len = sizeof(struct udphdr);
		udph->check = 0;
		break;
	}
	case IPPROTO_TCP: {
		struct tcphdr *tcph;

		tcph = skb_put_zero(skb, sizeof(struct tcphdr));
		tcph->source	= sport;
		tcph->dest	= dport;
		tcph->doff	= sizeof(struct tcphdr) / 4;
		tcph->rst = 1;
		tcph->check = ~tcp_v4_check(sizeof(struct tcphdr),
					    src, dst, 0);
		break;
	}
	case IPPROTO_ICMP: {
		struct icmphdr *icmph;

		icmph = skb_put_zero(skb, sizeof(struct icmphdr));
		icmph->type = ICMP_ECHO;
		icmph->code = 0;
	}
	}

	return skb;
}
