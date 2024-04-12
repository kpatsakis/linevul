struct sk_buff *llc_alloc_frame(struct sock *sk, struct net_device *dev,
				u8 type, u32 data_size)
{
	int hlen = type == LLC_PDU_TYPE_U ? 3 : 4;
	struct sk_buff *skb;

	hlen += llc_mac_header_len(dev->type);
	skb = alloc_skb(hlen + data_size, GFP_ATOMIC);

	if (skb) {
		skb_reset_mac_header(skb);
		skb_reserve(skb, hlen);
		skb_reset_network_header(skb);
		skb_reset_transport_header(skb);
		skb->protocol = htons(ETH_P_802_2);
		skb->dev      = dev;
		if (sk != NULL)
			skb_set_owner_w(skb, sk);
	}
	return skb;
}
