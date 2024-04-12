int SocketStream::DoSSLHandleCertError(int result) {
  DCHECK_EQ(STATE_NONE, next_state_);
  DCHECK(IsCertificateError(result));
  result = HandleCertificateError(result);
  if (result == OK || result == ERR_IO_PENDING)
    next_state_ = STATE_SSL_HANDLE_CERT_ERROR_COMPLETE;
  else
    next_state_ = STATE_CLOSE;
  return result;
}
