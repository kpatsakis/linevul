static void ip6mr_destroy_unres(struct mr6_table *mrt, struct mfc6_cache *c)
{
	struct net *net = read_pnet(&mrt->net);
	struct sk_buff *skb;

	atomic_dec(&mrt->cache_resolve_queue_len);

	while ((skb = skb_dequeue(&c->mfc_un.unres.unresolved)) != NULL) {
		if (ipv6_hdr(skb)->version == 0) {
			struct nlmsghdr *nlh = (struct nlmsghdr *)skb_pull(skb, sizeof(struct ipv6hdr));
			nlh->nlmsg_type = NLMSG_ERROR;
			nlh->nlmsg_len = nlmsg_msg_size(sizeof(struct nlmsgerr));
			skb_trim(skb, nlh->nlmsg_len);
			((struct nlmsgerr *)nlmsg_data(nlh))->error = -ETIMEDOUT;
			rtnl_unicast(skb, net, NETLINK_CB(skb).portid);
		} else
			kfree_skb(skb);
	}

	ip6mr_cache_free(c);
}
