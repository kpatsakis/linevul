static void __net_exit ip_rt_do_proc_exit(struct net *net)
{
	remove_proc_entry("rt_cache", net->proc_net_stat);
	remove_proc_entry("rt_cache", net->proc_net);
#ifdef CONFIG_IP_ROUTE_CLASSID
	remove_proc_entry("rt_acct", net->proc_net);
#endif
}
