int WebSocketExperimentTask::DoURLFetchComplete(int result) {
  url_fetcher_.reset();

  if (result < 0)
    return result;

  next_state_ = STATE_WEBSOCKET_CONNECT;
  return net::OK;
}
