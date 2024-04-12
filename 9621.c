static void __net_exit tcp4_proc_exit_net(struct net *net)
{
	tcp_proc_unregister(net, &tcp4_seq_afinfo);
}
