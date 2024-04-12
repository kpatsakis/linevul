void transport_attach(rdpTransport* transport, int sockfd)
{
	transport->TcpIn->sockfd = sockfd;

	transport->SplitInputOutput = FALSE;
	transport->TcpOut = transport->TcpIn;
}
