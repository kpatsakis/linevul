void WebSocketJob::OnConnected(
    SocketStream* socket, int max_pending_send_allowed) {
  if (state_ == CLOSED)
    return;
  DCHECK_EQ(CONNECTING, state_);
  if (delegate_)
    delegate_->OnConnected(socket, max_pending_send_allowed);
}
