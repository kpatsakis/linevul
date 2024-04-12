static int ipgre_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct ip_tunnel *t = netdev_priv(dev);
	struct ip_tunnel_parm *p = &t->parms;

	NLA_PUT_U32(skb, IFLA_GRE_LINK, p->link);
	NLA_PUT_BE16(skb, IFLA_GRE_IFLAGS, p->i_flags);
	NLA_PUT_BE16(skb, IFLA_GRE_OFLAGS, p->o_flags);
	NLA_PUT_BE32(skb, IFLA_GRE_IKEY, p->i_key);
	NLA_PUT_BE32(skb, IFLA_GRE_OKEY, p->o_key);
	NLA_PUT_BE32(skb, IFLA_GRE_LOCAL, p->iph.saddr);
	NLA_PUT_BE32(skb, IFLA_GRE_REMOTE, p->iph.daddr);
	NLA_PUT_U8(skb, IFLA_GRE_TTL, p->iph.ttl);
	NLA_PUT_U8(skb, IFLA_GRE_TOS, p->iph.tos);
	NLA_PUT_U8(skb, IFLA_GRE_PMTUDISC, !!(p->iph.frag_off & htons(IP_DF)));

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}
