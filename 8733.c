void AppCacheUpdateJob::URLFetcher::AddConditionalHeaders(
    const net::HttpResponseHeaders* headers) {
  DCHECK(request_.get() && headers);
  net::HttpRequestHeaders extra_headers;

  const std::string last_modified = "Last-Modified";
  std::string last_modified_value;
  headers->EnumerateHeader(NULL, last_modified, &last_modified_value);
  if (!last_modified_value.empty()) {
    extra_headers.SetHeader(net::HttpRequestHeaders::kIfModifiedSince,
                            last_modified_value);
  }

  const std::string etag = "ETag";
  std::string etag_value;
  headers->EnumerateHeader(NULL, etag, &etag_value);
  if (!etag_value.empty()) {
    extra_headers.SetHeader(net::HttpRequestHeaders::kIfNoneMatch,
                            etag_value);
  }
  if (!extra_headers.IsEmpty())
    request_->SetExtraRequestHeaders(extra_headers);
}
