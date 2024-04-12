int EncodeSSLConnectionStatus(int cipher_suite,
                              int compression,
                              int version) {
  return ((cipher_suite & SSL_CONNECTION_CIPHERSUITE_MASK) <<
          SSL_CONNECTION_CIPHERSUITE_SHIFT) |
         ((compression & SSL_CONNECTION_COMPRESSION_MASK) <<
          SSL_CONNECTION_COMPRESSION_SHIFT) |
         ((version & SSL_CONNECTION_VERSION_MASK) <<
          SSL_CONNECTION_VERSION_SHIFT);
}
