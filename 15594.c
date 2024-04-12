void ChromotingInstance::OnVideoDecodeError() {
  Disconnect();

  OnConnectionState(protocol::ConnectionToHost::FAILED,
                    protocol::INCOMPATIBLE_PROTOCOL);
}
