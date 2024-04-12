void ConnectionToClient::NotifyIfChannelsReady() {
  if (control_connected_ && input_connected_ && video_connected_)
    handler_->OnConnectionOpened(this);
}
