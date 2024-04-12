int MockNetworkTransaction::Start(const HttpRequestInfo* request,
                                  const CompletionCallback& callback,
                                  const BoundNetLog& net_log) {
  if (request_)
    return ERR_FAILED;

  request_ = request;
  return StartInternal(request, callback, net_log);
}
