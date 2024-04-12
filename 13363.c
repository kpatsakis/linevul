void ClientSession::OnConnectionOpened(
    protocol::ConnectionToClient* connection) {
  DCHECK_EQ(connection_.get(), connection);
  authenticated_ = true;
  event_handler_->OnSessionAuthenticated(this);
}
