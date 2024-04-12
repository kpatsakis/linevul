static void __exit sit_cleanup(void)
{
	xfrm4_tunnel_deregister(&sit_handler, AF_INET6);

	unregister_pernet_device(&sit_net_ops);
	rcu_barrier(); /* Wait for completion of call_rcu()'s */
}
