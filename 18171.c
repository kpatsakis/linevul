static int transport_read_nonblocking(rdpTransport* transport)
{
	int status;

	status = transport_read(transport, transport->ReceiveBuffer);

	if (status <= 0)
		return status;

	Stream_Seek(transport->ReceiveBuffer, status);

	return status;
}
