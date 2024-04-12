int WebSocketExperimentTask::DoWebSocketSendHello() {
  DCHECK(websocket_);

  next_state_ = STATE_WEBSOCKET_RECV_HELLO;

  websocket_echo_start_time_ = base::TimeTicks::Now();
  websocket_->Send(config_.websocket_hello_message);
  SetTimeout(config_.websocket_hello_echoback_deadline_ms);
  return net::ERR_IO_PENDING;
}
