static rx_handler_result_t macvlan_handle_frame(struct sk_buff **pskb)
{
	struct macvlan_port *port;
	struct sk_buff *skb = *pskb;
	const struct ethhdr *eth = eth_hdr(skb);
	const struct macvlan_dev *vlan;
	const struct macvlan_dev *src;
	struct net_device *dev;
	unsigned int len = 0;
	int ret = NET_RX_DROP;

	port = macvlan_port_get_rcu(skb->dev);
	if (is_multicast_ether_addr(eth->h_dest)) {
		src = macvlan_hash_lookup(port, eth->h_source);
		if (!src)
			/* frame comes from an external address */
			macvlan_broadcast(skb, port, NULL,
					  MACVLAN_MODE_PRIVATE |
					  MACVLAN_MODE_VEPA    |
					  MACVLAN_MODE_PASSTHRU|
					  MACVLAN_MODE_BRIDGE);
		else if (src->mode == MACVLAN_MODE_VEPA)
			/* flood to everyone except source */
			macvlan_broadcast(skb, port, src->dev,
					  MACVLAN_MODE_VEPA |
					  MACVLAN_MODE_BRIDGE);
		else if (src->mode == MACVLAN_MODE_BRIDGE)
			/*
			 * flood only to VEPA ports, bridge ports
			 * already saw the frame on the way out.
			 */
			macvlan_broadcast(skb, port, src->dev,
					  MACVLAN_MODE_VEPA);
		return RX_HANDLER_PASS;
	}

	if (port->passthru)
		vlan = list_first_entry(&port->vlans, struct macvlan_dev, list);
	else
		vlan = macvlan_hash_lookup(port, eth->h_dest);
	if (vlan == NULL)
		return RX_HANDLER_PASS;

	dev = vlan->dev;
	if (unlikely(!(dev->flags & IFF_UP))) {
		kfree_skb(skb);
		return RX_HANDLER_CONSUMED;
	}
	len = skb->len + ETH_HLEN;
	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	skb->dev = dev;
	skb->pkt_type = PACKET_HOST;

	ret = vlan->receive(skb);

out:
	macvlan_count_rx(vlan, len, ret == NET_RX_SUCCESS, 0);
	return RX_HANDLER_CONSUMED;
}
