void HWNDMessageHandler::OnDestroy() {
  delegate_->HandleDestroying();
}
