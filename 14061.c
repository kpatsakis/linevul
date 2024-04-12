void WebSocket::DetachDelegate() {
  if (!delegate_)
    return;
  delegate_ = NULL;
  Close();
}
