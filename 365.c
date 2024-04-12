void skb_set_dev(struct sk_buff *skb, struct net_device *dev)
{
	skb_dst_drop(skb);
	if (skb->dev && !net_eq(dev_net(skb->dev), dev_net(dev))) {
		secpath_reset(skb);
		nf_reset(skb);
		skb_init_secmark(skb);
		skb->mark = 0;
		skb->priority = 0;
		skb->nf_trace = 0;
		skb->ipvs_property = 0;
#ifdef CONFIG_NET_SCHED
		skb->tc_index = 0;
#endif
	}
	skb->dev = dev;
}
