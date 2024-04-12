void tcpv6_exit(void)
{
	unregister_pernet_subsys(&tcpv6_net_ops);
	inet6_unregister_protosw(&tcpv6_protosw);
	inet6_del_protocol(&tcpv6_protocol, IPPROTO_TCP);
}
