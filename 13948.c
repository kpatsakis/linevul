void ServerWrapper::OnWebSocketRequest(
    int connection_id,
    const net::HttpServerRequestInfo& request) {
  BrowserThread::PostTask(
      BrowserThread::UI, FROM_HERE,
      base::BindOnce(&DevToolsHttpHandler::OnWebSocketRequest, handler_,
                     connection_id, request));
}
