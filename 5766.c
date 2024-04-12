WebURLRequest::RequestContext ResourceFetcher::DetermineRequestContext(
    Resource::Type type) const {
  return DetermineRequestContext(type, Context().IsMainFrame());
}
