WebRunnerBrowserContext::CreateMediaRequestContext() {
  DCHECK(url_request_getter_.get());
  return url_request_getter_.get();
}
