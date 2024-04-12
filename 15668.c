net::SocketStreamJob* WebSocketJobFactory(
    const GURL& url, net::SocketStream::Delegate* delegate) {
  net::WebSocketJob* job = new net::WebSocketJob(delegate);
  job->InitSocketStream(new net::SocketStream(url, job));
  return job;
}
