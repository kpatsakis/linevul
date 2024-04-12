static NOINLINE void send_NAK(struct dhcp_packet *oldpacket)
{
	struct dhcp_packet packet;

	init_packet(&packet, oldpacket, DHCPNAK);

	log1("sending %s", "NAK");
	send_packet(&packet, /*force_bcast:*/ 1);
}
