ResourceRequest CreateXHRRequestWithOrigin(const char* origin) {
  ResourceRequest request = CreateXHRRequest("http://bar.com/simple_page.html");
  request.site_for_cookies = GURL(origin);
  request.headers.SetHeader(net::HttpRequestHeaders::kOrigin, origin);
  return request;
}
