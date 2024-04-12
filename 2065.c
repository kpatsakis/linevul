void UDPSocketLibevent::WriteWatcher::OnFileCanWriteWithoutBlocking(int) {
  if (!socket_->write_callback_.is_null())
    socket_->DidCompleteWrite();
}
