void WebSocketJob::OnCloseSpdyStream() {
  spdy_websocket_stream_.reset();
  OnClose(socket_);
}
