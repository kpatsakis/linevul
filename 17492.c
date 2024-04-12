static inline struct sk_buff *handle_ing(struct sk_buff *skb,
					 struct packet_type **pt_prev,
					 int *ret, struct net_device *orig_dev)
{
	if (skb->dev->rx_queue.qdisc == &noop_qdisc)
		goto out;

	if (*pt_prev) {
		*ret = deliver_skb(skb, *pt_prev, orig_dev);
		*pt_prev = NULL;
	}

	switch (ing_filter(skb)) {
	case TC_ACT_SHOT:
	case TC_ACT_STOLEN:
		kfree_skb(skb);
		return NULL;
	}

out:
	skb->tc_verd = 0;
	return skb;
}
