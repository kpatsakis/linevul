RTCPeerConnectionHandlerChromium::RTCPeerConnectionHandlerChromium(RTCPeerConnectionHandlerClient* client)
    : m_client(client)
{
    ASSERT(m_client);
}
