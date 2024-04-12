static int __init init_ipv4_mibs(void)
{
	return register_pernet_subsys(&ipv4_mib_ops);
}
