int UDPSocketLibevent::LeaveGroup(const IPAddressNumber& group_address) const {
  DCHECK(CalledOnValidThread());

  if (!is_connected())
    return ERR_SOCKET_NOT_CONNECTED;

  switch (group_address.size()) {
    case kIPv4AddressSize: {
      if (addr_family_ != AF_INET)
        return ERR_ADDRESS_INVALID;
      ip_mreq mreq;
      mreq.imr_interface.s_addr = INADDR_ANY;
      memcpy(&mreq.imr_multiaddr, &group_address[0], kIPv4AddressSize);
      int rv = setsockopt(socket_, IPPROTO_IP, IP_DROP_MEMBERSHIP,
                          &mreq, sizeof(mreq));
      if (rv < 0)
        return MapSystemError(errno);
      return OK;
    }
    case kIPv6AddressSize: {
      if (addr_family_ != AF_INET6)
        return ERR_ADDRESS_INVALID;
      ipv6_mreq mreq;
      mreq.ipv6mr_interface = 0;  // 0 indicates default multicast interface.
      memcpy(&mreq.ipv6mr_multiaddr, &group_address[0], kIPv6AddressSize);
      int rv = setsockopt(socket_, IPPROTO_IPV6, IPV6_LEAVE_GROUP,
                          &mreq, sizeof(mreq));
      if (rv < 0)
        return MapSystemError(errno);
      return OK;
    }
    default:
      NOTREACHED() << "Invalid address family";
      return ERR_ADDRESS_INVALID;
  }
}
