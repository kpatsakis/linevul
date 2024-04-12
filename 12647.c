static int ip6mr_forward2(struct net *net, struct mr6_table *mrt,
			  struct sk_buff *skb, struct mfc6_cache *c, int vifi)
{
	struct ipv6hdr *ipv6h;
	struct mif_device *vif = &mrt->vif6_table[vifi];
	struct net_device *dev;
	struct dst_entry *dst;
	struct flowi6 fl6;

	if (!vif->dev)
		goto out_free;

#ifdef CONFIG_IPV6_PIMSM_V2
	if (vif->flags & MIFF_REGISTER) {
		vif->pkt_out++;
		vif->bytes_out += skb->len;
		vif->dev->stats.tx_bytes += skb->len;
		vif->dev->stats.tx_packets++;
		ip6mr_cache_report(mrt, skb, vifi, MRT6MSG_WHOLEPKT);
		goto out_free;
	}
#endif

	ipv6h = ipv6_hdr(skb);

	fl6 = (struct flowi6) {
		.flowi6_oif = vif->link,
		.daddr = ipv6h->daddr,
	};

	dst = ip6_route_output(net, NULL, &fl6);
	if (dst->error) {
		dst_release(dst);
		goto out_free;
	}

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	/*
	 * RFC1584 teaches, that DVMRP/PIM router must deliver packets locally
	 * not only before forwarding, but after forwarding on all output
	 * interfaces. It is clear, if mrouter runs a multicasting
	 * program, it should receive packets not depending to what interface
	 * program is joined.
	 * If we will not make it, the program will have to join on all
	 * interfaces. On the other hand, multihoming host (or router, but
	 * not mrouter) cannot join to more than one interface - it will
	 * result in receiving multiple packets.
	 */
	dev = vif->dev;
	skb->dev = dev;
	vif->pkt_out++;
	vif->bytes_out += skb->len;

	/* We are about to write */
	/* XXX: extension headers? */
	if (skb_cow(skb, sizeof(*ipv6h) + LL_RESERVED_SPACE(dev)))
		goto out_free;

	ipv6h = ipv6_hdr(skb);
	ipv6h->hop_limit--;

	IP6CB(skb)->flags |= IP6SKB_FORWARDED;

	return NF_HOOK(NFPROTO_IPV6, NF_INET_FORWARD,
		       net, NULL, skb, skb->dev, dev,
		       ip6mr_forward2_finish);

out_free:
	kfree_skb(skb);
	return 0;
}
