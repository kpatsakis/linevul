static int hsr_dev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct hsr_priv *hsr = netdev_priv(dev);
	struct hsr_port *master;

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	skb->dev = master->dev;
	hsr_forward_skb(skb, master);

	return NETDEV_TX_OK;
}
