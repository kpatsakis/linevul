int WebSocketExperimentTask::DoWebSocketConnect() {
  DCHECK(!websocket_);

  websocket_ = context_->CreateWebSocket(config_, this);
  if (!websocket_) {
    next_state_ = STATE_NONE;
    return net::ERR_UNEXPECTED;
  }
  next_state_ = STATE_WEBSOCKET_CONNECT_COMPLETE;
  websocket_connect_start_time_ = base::TimeTicks::Now();
  websocket_->Connect();

  SetTimeout(config_.websocket_onopen_deadline_ms);
  return net::ERR_IO_PENDING;
}
