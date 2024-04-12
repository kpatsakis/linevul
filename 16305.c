int UDPSocketLibevent::SetMulticastLoopbackMode(bool loopback) {
  DCHECK(CalledOnValidThread());
  if (is_connected())
    return ERR_SOCKET_IS_CONNECTED;

  if (loopback)
    socket_options_ |= SOCKET_OPTION_MULTICAST_LOOP;
  else
    socket_options_ &= ~SOCKET_OPTION_MULTICAST_LOOP;
  return OK;
}
