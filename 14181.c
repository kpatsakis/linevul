void SocketStreamDispatcherHost::ContinueSSLRequest(
    const content::GlobalRequestID& id) {
  int socket_id = id.request_id;
  DVLOG(1) << "SocketStreamDispatcherHost::ContinueSSLRequest socket_id="
           << socket_id;
  DCHECK_NE(content::kNoSocketId, socket_id);
  SocketStreamHost* socket_stream_host = hosts_.Lookup(socket_id);
  DCHECK(socket_stream_host);
  socket_stream_host->ContinueDespiteError();
}
