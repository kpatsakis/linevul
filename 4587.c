static void PreserveRequestHeaders_Handler(
    const net::HttpRequestInfo* request,
    std::string* response_status,
    std::string* response_headers,
    std::string* response_data) {
  EXPECT_TRUE(request->extra_headers.HasHeader(kExtraHeaderKey));
}
