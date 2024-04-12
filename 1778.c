int GetNetSSLVersion(SSL* ssl) {
  switch (SSL_version(ssl)) {
    case SSL2_VERSION:
      return SSL_CONNECTION_VERSION_SSL2;
    case SSL3_VERSION:
      return SSL_CONNECTION_VERSION_SSL3;
    case TLS1_VERSION:
      return SSL_CONNECTION_VERSION_TLS1;
    case 0x0302:
      return SSL_CONNECTION_VERSION_TLS1_1;
    case 0x0303:
      return SSL_CONNECTION_VERSION_TLS1_2;
    default:
      return SSL_CONNECTION_VERSION_UNKNOWN;
  }
}
