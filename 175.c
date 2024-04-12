int HttpProxyClientSocket::DoGenerateAuthToken() {
  next_state_ = STATE_GENERATE_AUTH_TOKEN_COMPLETE;
  return auth_->MaybeGenerateAuthToken(&request_, io_callback_, net_log_);
}
