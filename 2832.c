static int __net_init ip6_tables_net_init(struct net *net)
{
	return xt_proto_init(net, NFPROTO_IPV6);
}
