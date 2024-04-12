static void __net_exit raw6_exit_net(struct net *net)
{
	remove_proc_entry("raw6", net->proc_net);
}
