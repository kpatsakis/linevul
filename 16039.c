ssh_packet_log_type(u_char type)
{
	switch (type) {
	case SSH2_MSG_CHANNEL_DATA:
	case SSH2_MSG_CHANNEL_EXTENDED_DATA:
	case SSH2_MSG_CHANNEL_WINDOW_ADJUST:
		return 0;
	default:
		return 1;
	}
}
