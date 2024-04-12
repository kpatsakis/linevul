BOOL transport_set_blocking_mode(rdpTransport* transport, BOOL blocking)
{
	BOOL status;

	status = TRUE;
	transport->blocking = blocking;

	if (transport->SplitInputOutput)
	{
		status &= tcp_set_blocking_mode(transport->TcpIn, blocking);
		status &= tcp_set_blocking_mode(transport->TcpOut, blocking);
	}
	else
	{
		status &= tcp_set_blocking_mode(transport->TcpIn, blocking);
	}

	if (transport->layer == TRANSPORT_LAYER_TSG)
	{
		tsg_set_blocking_mode(transport->tsg, blocking);
	}

	return status;
}
