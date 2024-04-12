void DevToolsDataSource::OnURLFetchComplete(const net::URLFetcher* source) {
  DCHECK(source);
  PendingRequestsMap::iterator it = pending_.find(source);
  DCHECK(it != pending_.end());
  std::string response;
  source->GetResponseAsString(&response);
  delete source;
  it->second.Run(base::RefCountedString::TakeString(&response));
  pending_.erase(it);
}
