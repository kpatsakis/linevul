void HttpProxyClientSocket::DoCallback(int result) {
  DCHECK_NE(ERR_IO_PENDING, result);
  DCHECK(!user_callback_.is_null());

  CompletionCallback c = user_callback_;
  user_callback_.Reset();
  c.Run(result);
}
