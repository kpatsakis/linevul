static NOINLINE int send_select(uint32_t xid, uint32_t server, uint32_t requested)
{
	struct dhcp_packet packet;
	struct in_addr temp_addr;

/*
 * RFC 2131 4.3.2 DHCPREQUEST message
 * ...
 * If the DHCPREQUEST message contains a 'server identifier'
 * option, the message is in response to a DHCPOFFER message.
 * Otherwise, the message is a request to verify or extend an
 * existing lease. If the client uses a 'client identifier'
 * in a DHCPREQUEST message, it MUST use that same 'client identifier'
 * in all subsequent messages. If the client included a list
 * of requested parameters in a DHCPDISCOVER message, it MUST
 * include that list in all subsequent messages.
 */
	/* Fill in: op, htype, hlen, cookie, chaddr fields,
	 * random xid field (we override it below),
	 * client-id option (unless -C), message type option:
	 */
	init_packet(&packet, DHCPREQUEST);

	packet.xid = xid;
	udhcp_add_simple_option(&packet, DHCP_REQUESTED_IP, requested);

	udhcp_add_simple_option(&packet, DHCP_SERVER_ID, server);

	/* Add options: maxsize,
	 * optionally: hostname, fqdn, vendorclass,
	 * "param req" option according to -O, and options specified with -x
	 */
	add_client_options(&packet);

	temp_addr.s_addr = requested;
	bb_error_msg("sending select for %s", inet_ntoa(temp_addr));
	return raw_bcast_from_client_config_ifindex(&packet, INADDR_ANY);
}
