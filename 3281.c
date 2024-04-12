static void sctp_v6_from_skb(union sctp_addr *addr,struct sk_buff *skb,
			     int is_saddr)
{
	__be16 *port;
	struct sctphdr *sh;

	port = &addr->v6.sin6_port;
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_flowinfo = 0; /* FIXME */
	addr->v6.sin6_scope_id = ((struct inet6_skb_parm *)skb->cb)->iif;

	sh = sctp_hdr(skb);
	if (is_saddr) {
		*port  = sh->source;
		addr->v6.sin6_addr = ipv6_hdr(skb)->saddr;
	} else {
		*port = sh->dest;
		addr->v6.sin6_addr = ipv6_hdr(skb)->daddr;
	}
}
