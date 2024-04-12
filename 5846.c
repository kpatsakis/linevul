int SpdyProxyClientSocket::GetPeerAddress(IPEndPoint* address) const {
  if (!IsConnected())
    return ERR_SOCKET_NOT_CONNECTED;
  return spdy_stream_->GetPeerAddress(address);
}
