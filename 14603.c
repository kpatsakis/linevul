int SocketStream::DoSecureProxyConnect() {
  DCHECK(factory_);
  SSLClientSocketContext ssl_context;
  ssl_context.cert_verifier = context_->cert_verifier();
  ssl_context.transport_security_state = context_->transport_security_state();
  ssl_context.server_bound_cert_service = context_->server_bound_cert_service();
  socket_.reset(factory_->CreateSSLClientSocket(
      socket_.release(),
      proxy_info_.proxy_server().host_port_pair(),
      proxy_ssl_config_,
      ssl_context));
  next_state_ = STATE_SECURE_PROXY_CONNECT_COMPLETE;
  metrics_->OnCountConnectionType(SocketStreamMetrics::SECURE_PROXY_CONNECTION);
  return socket_->Connect(io_callback_);
}
