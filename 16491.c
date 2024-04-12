  static void MakeRequestFailOnIO(const std::string& host) {
    net::URLRequestFilter* filter = net::URLRequestFilter::GetInstance();
    filter->AddHostnameInterceptor("http", host,
                                   std::unique_ptr<net::URLRequestInterceptor>(
                                       new FailedJobInterceptor()));
    filter->AddHostnameInterceptor("https", host,
                                   std::unique_ptr<net::URLRequestInterceptor>(
                                       new FailedJobInterceptor()));
  }
