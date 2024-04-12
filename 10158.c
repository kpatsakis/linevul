int SSLClientSocketOpenSSL::GetLocalAddress(IPEndPoint* addressList) const {
  return transport_->socket()->GetLocalAddress(addressList);
}
