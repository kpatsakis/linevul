config_ntpd(
	config_tree *ptree
	)
{
	config_nic_rules(ptree);
	io_open_sockets();
	config_monitor(ptree);
	config_auth(ptree);
	config_tos(ptree);
	config_access(ptree);
	config_tinker(ptree);
	config_system_opts(ptree);
	config_logconfig(ptree);
	config_phone(ptree);
	config_setvar(ptree);
	config_ttl(ptree);
	config_trap(ptree);
	config_vars(ptree);
	config_other_modes(ptree);
	config_peers(ptree);
	config_unpeers(ptree);
	config_fudge(ptree);
	config_qos(ptree);

#ifdef TEST_BLOCKING_WORKER
	{
		struct addrinfo hints;

		memset(&hints, 0, sizeof(hints));
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		getaddrinfo_sometime("www.cnn.com", "ntp", &hints,
				     INITIAL_DNS_RETRY,
				     gai_test_callback, (void *)1);
		hints.ai_family = AF_INET6;
		getaddrinfo_sometime("ipv6.google.com", "ntp", &hints, 
				     INITIAL_DNS_RETRY,
				     gai_test_callback, (void *)0x600);
	}
#endif
}
