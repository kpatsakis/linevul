void irc_servers_setup_deinit(void)
{
	signal_remove("server setup fill reconn", (SIGNAL_FUNC) sig_server_setup_fill_reconn);
	signal_remove("server setup fill connect", (SIGNAL_FUNC) sig_server_setup_fill_connect);
	signal_remove("server setup fill chatnet", (SIGNAL_FUNC) sig_server_setup_fill_chatnet);
	signal_remove("server setup read", (SIGNAL_FUNC) sig_server_setup_read);
	signal_remove("server setup saved", (SIGNAL_FUNC) sig_server_setup_saved);
}
