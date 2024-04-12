static void init_packet(struct dhcp_packet *packet, char type)
{
	uint16_t secs;

	/* Fill in: op, htype, hlen, cookie fields; message type option: */
	udhcp_init_header(packet, type);

	packet->xid = random_xid();

	client_config.last_secs = monotonic_sec();
	if (client_config.first_secs == 0)
		client_config.first_secs = client_config.last_secs;
	secs = client_config.last_secs - client_config.first_secs;
	packet->secs = htons(secs);

	memcpy(packet->chaddr, client_config.client_mac, 6);
	if (client_config.clientid)
		udhcp_add_binary_option(packet, client_config.clientid);
}
