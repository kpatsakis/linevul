static void ip_cmsg_recv_dstaddr(struct msghdr *msg, struct sk_buff *skb)
{
	struct sockaddr_in sin;
	const struct iphdr *iph = ip_hdr(skb);
	__be16 *ports = (__be16 *)skb_transport_header(skb);

	if (skb_transport_offset(skb) + 4 > skb->len)
		return;

	/* All current transport protocols have the port numbers in the
	 * first four bytes of the transport header and this function is
	 * written with this assumption in mind.
	 */

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = iph->daddr;
	sin.sin_port = ports[1];
	memset(sin.sin_zero, 0, sizeof(sin.sin_zero));

	put_cmsg(msg, SOL_IP, IP_ORIGDSTADDR, sizeof(sin), &sin);
}
