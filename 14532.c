persistent_available_p (const char *host, int port, bool ssl,
                        bool *host_lookup_failed)
{
  /* First, check whether a persistent connection is active at all.  */
  if (!pconn_active)
    return false;

  /* If we want SSL and the last connection wasn't or vice versa,
     don't use it.  Checking for host and port is not enough because
     HTTP and HTTPS can apparently coexist on the same port.  */
  if (ssl != pconn.ssl)
    return false;

  /* If we're not connecting to the same port, we're not interested. */
  if (port != pconn.port)
    return false;

  /* If the host is the same, we're in business.  If not, there is
     still hope -- read below.  */
  if (0 != strcasecmp (host, pconn.host))
    {
      /* Check if pconn.socket is talking to HOST under another name.
         This happens often when both sites are virtual hosts
         distinguished only by name and served by the same network
         interface, and hence the same web server (possibly set up by
         the ISP and serving many different web sites).  This
         admittedly unconventional optimization does not contradict
         HTTP and works well with popular server software.  */

      bool found;
      ip_address ip;
      struct address_list *al;

      if (ssl)
        /* Don't try to talk to two different SSL sites over the same
           secure connection!  (Besides, it's not clear that
           name-based virtual hosting is even possible with SSL.)  */
        return false;

      /* If pconn.socket's peer is one of the IP addresses HOST
         resolves to, pconn.socket is for all intents and purposes
         already talking to HOST.  */

      if (!socket_ip_address (pconn.socket, &ip, ENDPOINT_PEER))
        {
          /* Can't get the peer's address -- something must be very
             wrong with the connection.  */
          invalidate_persistent ();
          return false;
        }
      al = lookup_host (host, 0);
      if (!al)
        {
          *host_lookup_failed = true;
          return false;
        }

      found = address_list_contains (al, &ip);
      address_list_release (al);

      if (!found)
        return false;

      /* The persistent connection's peer address was found among the
         addresses HOST resolved to; therefore, pconn.sock is in fact
         already talking to HOST -- no need to reconnect.  */
    }

  /* Finally, check whether the connection is still open.  This is
     important because most servers implement liberal (short) timeout
     on persistent connections.  Wget can of course always reconnect
     if the connection doesn't work out, but it's nicer to know in
     advance.  This test is a logical followup of the first test, but
     is "expensive" and therefore placed at the end of the list.

     (Current implementation of test_socket_open has a nice side
     effect that it treats sockets with pending data as "closed".
     This is exactly what we want: if a broken server sends message
     body in response to HEAD, or if it sends more than conent-length
     data, we won't reuse the corrupted connection.)  */

  if (!test_socket_open (pconn.socket))
    {
      /* Oops, the socket is no longer open.  Now that we know that,
         let's invalidate the persistent connection before returning
         0.  */
      invalidate_persistent ();
      return false;
    }

  return true;
}
