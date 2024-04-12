static void __net_exit ip6_tnl_exit_net(struct net *net)
{
	struct ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	rtnl_lock();
	ip6_tnl_destroy_tunnels(ip6n);
	rtnl_unlock();
}
