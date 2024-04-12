int SocketStream::AllowCertErrorForReconnection(SSLConfig* ssl_config) {
  DCHECK(ssl_config);
  SSLClientSocket* ssl_socket = static_cast<SSLClientSocket*>(socket_.get());
  SSLInfo ssl_info;
  ssl_socket->GetSSLInfo(&ssl_info);
  if (ssl_info.cert.get() == NULL ||
      ssl_config->IsAllowedBadCert(ssl_info.cert.get(), NULL)) {
    next_state_ = STATE_CLOSE;
    return ERR_UNEXPECTED;
  }
  SSLConfig::CertAndStatus bad_cert;
  if (!X509Certificate::GetDEREncoded(ssl_info.cert->os_cert_handle(),
                                      &bad_cert.der_cert)) {
    next_state_ = STATE_CLOSE;
    return ERR_UNEXPECTED;
  }
  bad_cert.cert_status = ssl_info.cert_status;
  ssl_config->allowed_bad_certs.push_back(bad_cert);
  socket_->Disconnect();
  socket_.reset();
  next_state_ = STATE_TCP_CONNECT;
  return OK;
}
