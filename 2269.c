void DevToolsUIBindings::LoadNetworkResource(const DispatchCallback& callback,
                                             const std::string& url,
                                             const std::string& headers,
                                             int stream_id) {
  GURL gurl(url);
  if (!gurl.is_valid()) {
    base::DictionaryValue response;
    response.SetInteger("statusCode", 404);
    callback.Run(&response);
    return;
  }

  net::URLFetcher* fetcher =
      net::URLFetcher::Create(gurl, net::URLFetcher::GET, this).release();
  pending_requests_[fetcher] = callback;
  fetcher->SetRequestContext(profile_->GetRequestContext());
  fetcher->SetExtraRequestHeaders(headers);
  fetcher->SaveResponseWithWriter(
      std::unique_ptr<net::URLFetcherResponseWriter>(
          new ResponseWriter(weak_factory_.GetWeakPtr(), stream_id)));
  fetcher->Start();
}
