static void icmp_unreach(struct sk_buff *skb)
{
	const struct iphdr *iph;
	struct icmphdr *icmph;
	int hash, protocol;
	const struct net_protocol *ipprot;
	u32 info = 0;
	struct net *net;

	net = dev_net(skb_dst(skb)->dev);

	/*
	 *	Incomplete header ?
	 * 	Only checks for the IP header, there should be an
	 *	additional check for longer headers in upper levels.
	 */

	if (!pskb_may_pull(skb, sizeof(struct iphdr)))
		goto out_err;

	icmph = icmp_hdr(skb);
	iph   = (const struct iphdr *)skb->data;

	if (iph->ihl < 5) /* Mangled header, drop. */
		goto out_err;

	if (icmph->type == ICMP_DEST_UNREACH) {
		switch (icmph->code & 15) {
		case ICMP_NET_UNREACH:
		case ICMP_HOST_UNREACH:
		case ICMP_PROT_UNREACH:
		case ICMP_PORT_UNREACH:
			break;
		case ICMP_FRAG_NEEDED:
			if (ipv4_config.no_pmtu_disc) {
				LIMIT_NETDEBUG(KERN_INFO "ICMP: %pI4: fragmentation needed and DF set.\n",
					       &iph->daddr);
			} else {
				info = ip_rt_frag_needed(net, iph,
							 ntohs(icmph->un.frag.mtu),
							 skb->dev);
				if (!info)
					goto out;
			}
			break;
		case ICMP_SR_FAILED:
			LIMIT_NETDEBUG(KERN_INFO "ICMP: %pI4: Source Route Failed.\n",
				       &iph->daddr);
			break;
		default:
			break;
		}
		if (icmph->code > NR_ICMP_UNREACH)
			goto out;
	} else if (icmph->type == ICMP_PARAMETERPROB)
		info = ntohl(icmph->un.gateway) >> 24;

	/*
	 *	Throw it at our lower layers
	 *
	 *	RFC 1122: 3.2.2 MUST extract the protocol ID from the passed
	 *		  header.
	 *	RFC 1122: 3.2.2.1 MUST pass ICMP unreach messages to the
	 *		  transport layer.
	 *	RFC 1122: 3.2.2.2 MUST pass ICMP time expired messages to
	 *		  transport layer.
	 */

	/*
	 *	Check the other end isn't violating RFC 1122. Some routers send
	 *	bogus responses to broadcast frames. If you see this message
	 *	first check your netmask matches at both ends, if it does then
	 *	get the other vendor to fix their kit.
	 */

	if (!net->ipv4.sysctl_icmp_ignore_bogus_error_responses &&
	    inet_addr_type(net, iph->daddr) == RTN_BROADCAST) {
		if (net_ratelimit())
			printk(KERN_WARNING "%pI4 sent an invalid ICMP "
					    "type %u, code %u "
					    "error to a broadcast: %pI4 on %s\n",
			       &ip_hdr(skb)->saddr,
			       icmph->type, icmph->code,
			       &iph->daddr,
			       skb->dev->name);
		goto out;
	}

	/* Checkin full IP header plus 8 bytes of protocol to
	 * avoid additional coding at protocol handlers.
	 */
	if (!pskb_may_pull(skb, iph->ihl * 4 + 8))
		goto out;

	iph = (const struct iphdr *)skb->data;
	protocol = iph->protocol;

	/*
	 *	Deliver ICMP message to raw sockets. Pretty useless feature?
	 */
	raw_icmp_error(skb, protocol, info);

	hash = protocol & (MAX_INET_PROTOS - 1);
	rcu_read_lock();
	ipprot = rcu_dereference(inet_protos[hash]);
	if (ipprot && ipprot->err_handler)
		ipprot->err_handler(skb, info);
	rcu_read_unlock();

out:
	return;
out_err:
	ICMP_INC_STATS_BH(net, ICMP_MIB_INERRORS);
	goto out;
}
