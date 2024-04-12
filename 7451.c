void WebSocketJob::DetachDelegate() {
  state_ = CLOSED;
  WebSocketThrottle::GetInstance()->RemoveFromQueue(this);
  WebSocketThrottle::GetInstance()->WakeupSocketIfNecessary();

  scoped_refptr<WebSocketJob> protect(this);

  delegate_ = NULL;
  if (socket_)
    socket_->DetachDelegate();
  socket_ = NULL;
  if (callback_) {
    waiting_ = false;
    callback_ = NULL;
    Release();  // Balanced with OnStartOpenConnection().
  }
}
