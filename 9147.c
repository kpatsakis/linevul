static int ipv6_rthdr_rcv(struct sk_buff *skb)
{
	struct inet6_skb_parm *opt = IP6CB(skb);
	struct in6_addr *addr = NULL;
	struct in6_addr daddr;
	struct inet6_dev *idev;
	int n, i;
	struct ipv6_rt_hdr *hdr;
	struct rt0_hdr *rthdr;
	struct net *net = dev_net(skb->dev);
	int accept_source_route = net->ipv6.devconf_all->accept_source_route;

	idev = __in6_dev_get(skb->dev);
	if (idev && accept_source_route > idev->cnf.accept_source_route)
		accept_source_route = idev->cnf.accept_source_route;

	if (!pskb_may_pull(skb, skb_transport_offset(skb) + 8) ||
	    !pskb_may_pull(skb, (skb_transport_offset(skb) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) {
		IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INHDRERRORS);
		kfree_skb(skb);
		return -1;
	}

	hdr = (struct ipv6_rt_hdr *)skb_transport_header(skb);

	if (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr) ||
	    skb->pkt_type != PACKET_HOST) {
		IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INADDRERRORS);
		kfree_skb(skb);
		return -1;
	}

looped_back:
	if (hdr->segments_left == 0) {
		switch (hdr->type) {
#if IS_ENABLED(CONFIG_IPV6_MIP6)
		case IPV6_SRCRT_TYPE_2:
			/* Silently discard type 2 header unless it was
			 * processed by own
			 */
			if (!addr) {
				IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
						 IPSTATS_MIB_INADDRERRORS);
				kfree_skb(skb);
				return -1;
			}
			break;
#endif
		default:
			break;
		}

		opt->lastopt = opt->srcrt = skb_network_header_len(skb);
		skb->transport_header += (hdr->hdrlen + 1) << 3;
		opt->dst0 = opt->dst1;
		opt->dst1 = 0;
		opt->nhoff = (&hdr->nexthdr) - skb_network_header(skb);
		return 1;
	}

	switch (hdr->type) {
#if IS_ENABLED(CONFIG_IPV6_MIP6)
	case IPV6_SRCRT_TYPE_2:
		if (accept_source_route < 0)
			goto unknown_rh;
		/* Silently discard invalid RTH type 2 */
		if (hdr->hdrlen != 2 || hdr->segments_left != 1) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_INHDRERRORS);
			kfree_skb(skb);
			return -1;
		}
		break;
#endif
	default:
		goto unknown_rh;
	}

	/*
	 *	This is the routing header forwarding algorithm from
	 *	RFC 2460, page 16.
	 */

	n = hdr->hdrlen >> 1;

	if (hdr->segments_left > n) {
		IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
				  ((&hdr->segments_left) -
				   skb_network_header(skb)));
		return -1;
	}

	/* We are about to mangle packet header. Be careful!
	   Do not damage packets queued somewhere.
	 */
	if (skb_cloned(skb)) {
		/* the copy is a forwarded packet */
		if (pskb_expand_head(skb, 0, 0, GFP_ATOMIC)) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_OUTDISCARDS);
			kfree_skb(skb);
			return -1;
		}
		hdr = (struct ipv6_rt_hdr *)skb_transport_header(skb);
	}

	if (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;

	i = n - --hdr->segments_left;

	rthdr = (struct rt0_hdr *) hdr;
	addr = rthdr->addr;
	addr += i - 1;

	switch (hdr->type) {
#if IS_ENABLED(CONFIG_IPV6_MIP6)
	case IPV6_SRCRT_TYPE_2:
		if (xfrm6_input_addr(skb, (xfrm_address_t *)addr,
				     (xfrm_address_t *)&ipv6_hdr(skb)->saddr,
				     IPPROTO_ROUTING) < 0) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_INADDRERRORS);
			kfree_skb(skb);
			return -1;
		}
		if (!ipv6_chk_home_addr(dev_net(skb_dst(skb)->dev), addr)) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_INADDRERRORS);
			kfree_skb(skb);
			return -1;
		}
		break;
#endif
	default:
		break;
	}

	if (ipv6_addr_is_multicast(addr)) {
		IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INADDRERRORS);
		kfree_skb(skb);
		return -1;
	}

	daddr = *addr;
	*addr = ipv6_hdr(skb)->daddr;
	ipv6_hdr(skb)->daddr = daddr;

	skb_dst_drop(skb);
	ip6_route_input(skb);
	if (skb_dst(skb)->error) {
		skb_push(skb, skb->data - skb_network_header(skb));
		dst_input(skb);
		return -1;
	}

	if (skb_dst(skb)->dev->flags&IFF_LOOPBACK) {
		if (ipv6_hdr(skb)->hop_limit <= 1) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_INHDRERRORS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPLIMIT,
				    0);
			kfree_skb(skb);
			return -1;
		}
		ipv6_hdr(skb)->hop_limit--;
		goto looped_back;
	}

	skb_push(skb, skb->data - skb_network_header(skb));
	dst_input(skb);
	return -1;

unknown_rh:
	IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_INHDRERRORS);
	icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
			  (&hdr->type) - skb_network_header(skb));
	return -1;
}
