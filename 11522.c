int WebRTCTransportImpl::SendPacket(int channel, const void* data, int len) {
  return network_->ReceivedRTPPacket(channel, data, len);
}
