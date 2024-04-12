int ip_mc_validate_source(struct sk_buff *skb, __be32 daddr, __be32 saddr,
			  u8 tos, struct net_device *dev,
			  struct in_device *in_dev, u32 *itag)
{
	int err;

	/* Primary sanity checks. */
	if (!in_dev)
		return -EINVAL;

	if (ipv4_is_multicast(saddr) || ipv4_is_lbcast(saddr) ||
	    skb->protocol != htons(ETH_P_IP))
		return -EINVAL;

	if (ipv4_is_loopback(saddr) && !IN_DEV_ROUTE_LOCALNET(in_dev))
		return -EINVAL;

	if (ipv4_is_zeronet(saddr)) {
		if (!ipv4_is_local_multicast(daddr) &&
		    ip_hdr(skb)->protocol != IPPROTO_IGMP)
			return -EINVAL;
	} else {
		err = fib_validate_source(skb, saddr, 0, tos, 0, dev,
					  in_dev, itag);
		if (err < 0)
			return err;
	}
	return 0;
}
