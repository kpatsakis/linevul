void servers_init(void)
{
	settings_add_bool("server", "resolve_prefer_ipv6", FALSE);
	settings_add_bool("server", "resolve_reverse_lookup", FALSE);
	lookup_servers = servers = NULL;

	signal_add("chat protocol deinit", (SIGNAL_FUNC) sig_chat_protocol_deinit);

	servers_reconnect_init();
	servers_setup_init();
}
