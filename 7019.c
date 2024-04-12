 void WebSocketJob::CloseInternal() {
  if (spdy_websocket_stream_.get())
    spdy_websocket_stream_->Close();
  if (socket_.get())
    socket_->Close();
}
