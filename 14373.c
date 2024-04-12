  std::unique_ptr<net::URLRequest> CreateAndExecuteRequest(const GURL& url) {
    std::unique_ptr<net::URLRequest> request(context_.CreateRequest(
        url, net::IDLE, &delegate_, TRAFFIC_ANNOTATION_FOR_TESTS));
    request->Start();
    drp_test_context_->RunUntilIdle();
    return request;
  }
