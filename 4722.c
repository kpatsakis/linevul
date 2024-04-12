static BOOL freerdp_peer_check_fds(freerdp_peer* client)
{
	int status;
	rdpRdp* rdp;

	rdp = client->context->rdp;

	status = rdp_check_fds(rdp);

	if (status < 0)
		return FALSE;

	return TRUE;
}
