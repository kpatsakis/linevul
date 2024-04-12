static int rdp_recv_callback(rdpTransport* transport, STREAM* s, void* extra)
{
	int status = 0;
	rdpRdp* rdp = (rdpRdp*) extra;

	switch (rdp->state)
	{
		case CONNECTION_STATE_NEGO:
			if (!rdp_client_connect_mcs_connect_response(rdp, s))
				status = -1;
			break;

		case CONNECTION_STATE_MCS_ATTACH_USER:
			if (!rdp_client_connect_mcs_attach_user_confirm(rdp, s))
				status = -1;
			break;

		case CONNECTION_STATE_MCS_CHANNEL_JOIN:
			if (!rdp_client_connect_mcs_channel_join_confirm(rdp, s))
				status = -1;
			break;

		case CONNECTION_STATE_LICENSE:
			if (!rdp_client_connect_license(rdp, s))
				status = -1;
			break;

		case CONNECTION_STATE_CAPABILITY:
			if (!rdp_client_connect_demand_active(rdp, s))
				status = -1;
			break;

		case CONNECTION_STATE_FINALIZATION:
			status = rdp_recv_pdu(rdp, s);
			if ((status >= 0) && (rdp->finalize_sc_pdus == FINALIZE_SC_COMPLETE))
				rdp->state = CONNECTION_STATE_ACTIVE;
			break;

		case CONNECTION_STATE_ACTIVE:
			status = rdp_recv_pdu(rdp, s);
			break;

		default:
			printf("Invalid state %d\n", rdp->state);
			status = -1;
			break;
	}

	return status;
}
