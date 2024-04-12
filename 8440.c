bool SocketStream::is_secure() const {
  return url_.SchemeIs("wss");
 }
