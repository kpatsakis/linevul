  bool SetClientSocketForSSL(SSL* ssl, SSLClientSocketOpenSSL* socket) {
    return SSL_set_ex_data(ssl, ssl_socket_data_index_, socket) != 0;
  }
