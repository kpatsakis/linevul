static void freerdp_peer_disconnect(freerdp_peer* client)
{
	transport_disconnect(client->context->rdp->transport);
}
