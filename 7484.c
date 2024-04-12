static int tcp6_gro_complete(struct sk_buff *skb)
{
	const struct ipv6hdr *iph = ipv6_hdr(skb);
	struct tcphdr *th = tcp_hdr(skb);

	th->check = ~tcp_v6_check(skb->len - skb_transport_offset(skb),
				  &iph->saddr, &iph->daddr, 0);
	skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;

	return tcp_gro_complete(skb);
}
