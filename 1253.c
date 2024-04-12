static void ETagGet_ConditionalRequest_NoStore_Handler(
    const net::HttpRequestInfo* request,
    std::string* response_status,
    std::string* response_headers,
    std::string* response_data) {
  EXPECT_TRUE(
      request->extra_headers.HasHeader(net::HttpRequestHeaders::kIfNoneMatch));
  response_status->assign("HTTP/1.1 304 Not Modified");
  response_headers->assign("Cache-Control: no-store\n");
  response_data->clear();
}
