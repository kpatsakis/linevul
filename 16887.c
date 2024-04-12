void irc_servers_reconnect_deinit(void)
{
	signal_remove("server connect copy", (SIGNAL_FUNC) sig_server_connect_copy);
	signal_remove("server reconnect save status", (SIGNAL_FUNC) sig_server_reconnect_save_status);
	signal_remove("event connected", (SIGNAL_FUNC) sig_connected);
	signal_remove("event 436", (SIGNAL_FUNC) event_nick_collision);
	signal_remove("event kill", (SIGNAL_FUNC) event_kill);
}
