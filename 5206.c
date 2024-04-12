int udp_gro_complete(struct sk_buff *skb, int nhoff)
{
	struct udp_offload_priv *uo_priv;
	__be16 newlen = htons(skb->len - nhoff);
	struct udphdr *uh = (struct udphdr *)(skb->data + nhoff);
	int err = -ENOSYS;

	uh->len = newlen;

	rcu_read_lock();

	uo_priv = rcu_dereference(udp_offload_base);
	for (; uo_priv != NULL; uo_priv = rcu_dereference(uo_priv->next)) {
		if (net_eq(read_pnet(&uo_priv->net), dev_net(skb->dev)) &&
		    uo_priv->offload->port == uh->dest &&
		    uo_priv->offload->callbacks.gro_complete)
			break;
	}

	if (uo_priv) {
		NAPI_GRO_CB(skb)->proto = uo_priv->offload->ipproto;
		err = uo_priv->offload->callbacks.gro_complete(skb,
				nhoff + sizeof(struct udphdr),
				uo_priv->offload);
	}

	rcu_read_unlock();

	if (skb->remcsum_offload)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TUNNEL_REMCSUM;

	skb->encapsulation = 1;
	skb_set_inner_mac_header(skb, nhoff + sizeof(struct udphdr));

	return err;
}
