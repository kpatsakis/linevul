void nicklist_init(void)
{
	signal_add_first("channel created", (SIGNAL_FUNC) sig_channel_created);
	signal_add("channel destroyed", (SIGNAL_FUNC) sig_channel_destroyed);
}
