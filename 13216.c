static __sum16 tcp_v4_checksum_init(struct sk_buff *skb)
{
	const struct iphdr *iph = ip_hdr(skb);

	if (skb->ip_summed == CHECKSUM_COMPLETE) {
		if (!tcp_v4_check(skb->len, iph->saddr,
				  iph->daddr, skb->csum)) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			return 0;
		}
	}

	skb->csum = csum_tcpudp_nofold(iph->saddr, iph->daddr,
				       skb->len, IPPROTO_TCP, 0);

	if (skb->len <= 76) {
		return __skb_checksum_complete(skb);
	}
	return 0;
}
