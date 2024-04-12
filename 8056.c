X509Certificate* SSLClientSocketOpenSSL::UpdateServerCert() {
  if (server_cert_.get())
    return server_cert_.get();

  crypto::ScopedOpenSSL<X509, X509_free> cert(SSL_get_peer_certificate(ssl_));
  if (!cert.get()) {
    LOG(WARNING) << "SSL_get_peer_certificate returned NULL";
    return NULL;
  }

  STACK_OF(X509)* chain = SSL_get_peer_cert_chain(ssl_);
  X509Certificate::OSCertHandles intermediates;
  if (chain) {
    for (int i = 0; i < sk_X509_num(chain); ++i)
      intermediates.push_back(sk_X509_value(chain, i));
  }
  server_cert_ = X509Certificate::CreateFromHandle(cert.get(), intermediates);
  DCHECK(server_cert_.get());

  return server_cert_.get();
}
