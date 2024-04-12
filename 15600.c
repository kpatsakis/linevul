int netif_rx_ni(struct sk_buff *skb)
{
	int err;

	preempt_disable();
	err = netif_rx(skb);
	if (local_softirq_pending())
		do_softirq();
	preempt_enable();

	return err;
}
