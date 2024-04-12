static void netlink_destroy_callback(struct netlink_callback *cb)
{
	kfree_skb(cb->skb);
	kfree(cb);
}
