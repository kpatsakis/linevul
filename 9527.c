net::URLRequestContextGetter* IOThread::system_url_request_context_getter() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  if (!system_url_request_context_getter_.get()) {
    InitSystemRequestContext();
  }
  return system_url_request_context_getter_.get();
}
