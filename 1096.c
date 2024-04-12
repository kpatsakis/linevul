ip6_tnl_err(struct sk_buff *skb, __u8 ipproto, struct inet6_skb_parm *opt,
	    u8 *type, u8 *code, int *msg, __u32 *info, int offset)
{
	struct ipv6hdr *ipv6h = (struct ipv6hdr *) skb->data;
	struct ip6_tnl *t;
	int rel_msg = 0;
	u8 rel_type = ICMPV6_DEST_UNREACH;
	u8 rel_code = ICMPV6_ADDR_UNREACH;
	__u32 rel_info = 0;
	__u16 len;
	int err = -ENOENT;

	/* If the packet doesn't contain the original IPv6 header we are
	   in trouble since we might need the source address for further
	   processing of the error. */

	rcu_read_lock();
	if ((t = ip6_tnl_lookup(dev_net(skb->dev), &ipv6h->daddr,
					&ipv6h->saddr)) == NULL)
		goto out;

	if (t->parms.proto != ipproto && t->parms.proto != 0)
		goto out;

	err = 0;

	switch (*type) {
		__u32 teli;
		struct ipv6_tlv_tnl_enc_lim *tel;
		__u32 mtu;
	case ICMPV6_DEST_UNREACH:
		if (net_ratelimit())
			printk(KERN_WARNING
			       "%s: Path to destination invalid "
			       "or inactive!\n", t->parms.name);
		rel_msg = 1;
		break;
	case ICMPV6_TIME_EXCEED:
		if ((*code) == ICMPV6_EXC_HOPLIMIT) {
			if (net_ratelimit())
				printk(KERN_WARNING
				       "%s: Too small hop limit or "
				       "routing loop in tunnel!\n",
				       t->parms.name);
			rel_msg = 1;
		}
		break;
	case ICMPV6_PARAMPROB:
		teli = 0;
		if ((*code) == ICMPV6_HDR_FIELD)
			teli = parse_tlv_tnl_enc_lim(skb, skb->data);

		if (teli && teli == *info - 2) {
			tel = (struct ipv6_tlv_tnl_enc_lim *) &skb->data[teli];
			if (tel->encap_limit == 0) {
				if (net_ratelimit())
					printk(KERN_WARNING
					       "%s: Too small encapsulation "
					       "limit or routing loop in "
					       "tunnel!\n", t->parms.name);
				rel_msg = 1;
			}
		} else if (net_ratelimit()) {
			printk(KERN_WARNING
			       "%s: Recipient unable to parse tunneled "
			       "packet!\n ", t->parms.name);
		}
		break;
	case ICMPV6_PKT_TOOBIG:
		mtu = *info - offset;
		if (mtu < IPV6_MIN_MTU)
			mtu = IPV6_MIN_MTU;
		t->dev->mtu = mtu;

		if ((len = sizeof (*ipv6h) + ntohs(ipv6h->payload_len)) > mtu) {
			rel_type = ICMPV6_PKT_TOOBIG;
			rel_code = 0;
			rel_info = mtu;
			rel_msg = 1;
		}
		break;
	}

	*type = rel_type;
	*code = rel_code;
	*info = rel_info;
	*msg = rel_msg;

out:
	rcu_read_unlock();
	return err;
}
