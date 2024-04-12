static void icmp_redirect(struct sk_buff *skb)
{
	const struct iphdr *iph;

	if (skb->len < sizeof(struct iphdr))
		goto out_err;

	/*
	 *	Get the copied header of the packet that caused the redirect
	 */
	if (!pskb_may_pull(skb, sizeof(struct iphdr)))
		goto out;

	iph = (const struct iphdr *)skb->data;

	switch (icmp_hdr(skb)->code & 7) {
	case ICMP_REDIR_NET:
	case ICMP_REDIR_NETTOS:
		/*
		 * As per RFC recommendations now handle it as a host redirect.
		 */
	case ICMP_REDIR_HOST:
	case ICMP_REDIR_HOSTTOS:
		ip_rt_redirect(ip_hdr(skb)->saddr, iph->daddr,
			       icmp_hdr(skb)->un.gateway,
			       iph->saddr, skb->dev);
		break;
	}
out:
	return;
out_err:
	ICMP_INC_STATS_BH(dev_net(skb->dev), ICMP_MIB_INERRORS);
	goto out;
}
