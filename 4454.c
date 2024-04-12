void ip6_datagram_recv_specific_ctl(struct sock *sk, struct msghdr *msg,
				    struct sk_buff *skb)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct inet6_skb_parm *opt = IP6CB(skb);
	unsigned char *nh = skb_network_header(skb);

	if (np->rxopt.bits.rxhlim) {
		int hlim = ipv6_hdr(skb)->hop_limit;
		put_cmsg(msg, SOL_IPV6, IPV6_HOPLIMIT, sizeof(hlim), &hlim);
	}

	if (np->rxopt.bits.rxtclass) {
		int tclass = ipv6_get_dsfield(ipv6_hdr(skb));
		put_cmsg(msg, SOL_IPV6, IPV6_TCLASS, sizeof(tclass), &tclass);
	}

	if (np->rxopt.bits.rxflow) {
		__be32 flowinfo = ip6_flowinfo((struct ipv6hdr *)nh);
		if (flowinfo)
			put_cmsg(msg, SOL_IPV6, IPV6_FLOWINFO, sizeof(flowinfo), &flowinfo);
	}

	/* HbH is allowed only once */
	if (np->rxopt.bits.hopopts && (opt->flags & IP6SKB_HOPBYHOP)) {
		u8 *ptr = nh + sizeof(struct ipv6hdr);
		put_cmsg(msg, SOL_IPV6, IPV6_HOPOPTS, (ptr[1]+1)<<3, ptr);
	}

	if (opt->lastopt &&
	    (np->rxopt.bits.dstopts || np->rxopt.bits.srcrt)) {
		/*
		 * Silly enough, but we need to reparse in order to
		 * report extension headers (except for HbH)
		 * in order.
		 *
		 * Also note that IPV6_RECVRTHDRDSTOPTS is NOT
		 * (and WILL NOT be) defined because
		 * IPV6_RECVDSTOPTS is more generic. --yoshfuji
		 */
		unsigned int off = sizeof(struct ipv6hdr);
		u8 nexthdr = ipv6_hdr(skb)->nexthdr;

		while (off <= opt->lastopt) {
			unsigned int len;
			u8 *ptr = nh + off;

			switch (nexthdr) {
			case IPPROTO_DSTOPTS:
				nexthdr = ptr[0];
				len = (ptr[1] + 1) << 3;
				if (np->rxopt.bits.dstopts)
					put_cmsg(msg, SOL_IPV6, IPV6_DSTOPTS, len, ptr);
				break;
			case IPPROTO_ROUTING:
				nexthdr = ptr[0];
				len = (ptr[1] + 1) << 3;
				if (np->rxopt.bits.srcrt)
					put_cmsg(msg, SOL_IPV6, IPV6_RTHDR, len, ptr);
				break;
			case IPPROTO_AH:
				nexthdr = ptr[0];
				len = (ptr[1] + 2) << 2;
				break;
			default:
				nexthdr = ptr[0];
				len = (ptr[1] + 1) << 3;
				break;
			}

			off += len;
		}
	}

	/* socket options in old style */
	if (np->rxopt.bits.rxoinfo) {
		struct in6_pktinfo src_info;

		src_info.ipi6_ifindex = opt->iif;
		src_info.ipi6_addr = ipv6_hdr(skb)->daddr;
		put_cmsg(msg, SOL_IPV6, IPV6_2292PKTINFO, sizeof(src_info), &src_info);
	}
	if (np->rxopt.bits.rxohlim) {
		int hlim = ipv6_hdr(skb)->hop_limit;
		put_cmsg(msg, SOL_IPV6, IPV6_2292HOPLIMIT, sizeof(hlim), &hlim);
	}
	if (np->rxopt.bits.ohopopts && (opt->flags & IP6SKB_HOPBYHOP)) {
		u8 *ptr = nh + sizeof(struct ipv6hdr);
		put_cmsg(msg, SOL_IPV6, IPV6_2292HOPOPTS, (ptr[1]+1)<<3, ptr);
	}
	if (np->rxopt.bits.odstopts && opt->dst0) {
		u8 *ptr = nh + opt->dst0;
		put_cmsg(msg, SOL_IPV6, IPV6_2292DSTOPTS, (ptr[1]+1)<<3, ptr);
	}
	if (np->rxopt.bits.osrcrt && opt->srcrt) {
		struct ipv6_rt_hdr *rthdr = (struct ipv6_rt_hdr *)(nh + opt->srcrt);
		put_cmsg(msg, SOL_IPV6, IPV6_2292RTHDR, (rthdr->hdrlen+1) << 3, rthdr);
	}
	if (np->rxopt.bits.odstopts && opt->dst1) {
		u8 *ptr = nh + opt->dst1;
		put_cmsg(msg, SOL_IPV6, IPV6_2292DSTOPTS, (ptr[1]+1)<<3, ptr);
	}
	if (np->rxopt.bits.rxorigdstaddr) {
		struct sockaddr_in6 sin6;
		__be16 *ports = (__be16 *) skb_transport_header(skb);

		if (skb_transport_offset(skb) + 4 <= skb->len) {
			/* All current transport protocols have the port numbers in the
			 * first four bytes of the transport header and this function is
			 * written with this assumption in mind.
			 */

			sin6.sin6_family = AF_INET6;
			sin6.sin6_addr = ipv6_hdr(skb)->daddr;
			sin6.sin6_port = ports[1];
			sin6.sin6_flowinfo = 0;
			sin6.sin6_scope_id =
				ipv6_iface_scope_id(&ipv6_hdr(skb)->daddr,
						    opt->iif);

			put_cmsg(msg, SOL_IPV6, IPV6_ORIGDSTADDR, sizeof(sin6), &sin6);
		}
	}
}
