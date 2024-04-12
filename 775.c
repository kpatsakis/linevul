static void sctp_inet6_skb_msgname(struct sk_buff *skb, char *msgname,
				   int *addr_len)
{
	struct sctphdr *sh;
	struct sockaddr_in6 *sin6;

	if (msgname) {
		sctp_inet6_msgname(msgname, addr_len);
		sin6 = (struct sockaddr_in6 *)msgname;
		sh = sctp_hdr(skb);
		sin6->sin6_port = sh->source;

		/* Map ipv4 address into v4-mapped-on-v6 address. */
		if (sctp_sk(skb->sk)->v4mapped &&
		    ip_hdr(skb)->version == 4) {
			sctp_v4_map_v6((union sctp_addr *)sin6);
			sin6->sin6_addr.s6_addr32[3] = ip_hdr(skb)->saddr;
			return;
		}

		/* Otherwise, just copy the v6 address. */
		sin6->sin6_addr = ipv6_hdr(skb)->saddr;
		if (ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LINKLOCAL) {
			struct sctp_ulpevent *ev = sctp_skb2event(skb);
			sin6->sin6_scope_id = ev->iif;
		}
	}
}
