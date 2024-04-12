void HttpNetworkTransactionTest::CheckErrorIsPassedBack(
    int error, IoMode mode) {
  HttpRequestInfo request_info;
  request_info.url = GURL("https://www.example.com/");
  request_info.method = "GET";
  request_info.load_flags = LOAD_NORMAL;
  request_info.traffic_annotation =
      net::MutableNetworkTrafficAnnotationTag(TRAFFIC_ANNOTATION_FOR_TESTS);

  SSLSocketDataProvider ssl_data(mode, OK);
  MockWrite data_writes[] = {
      MockWrite(mode, error),
  };
  StaticSocketDataProvider data(base::span<MockRead>(), data_writes);
  session_deps_.socket_factory->AddSocketDataProvider(&data);
  session_deps_.socket_factory->AddSSLSocketDataProvider(&ssl_data);

  std::unique_ptr<HttpNetworkSession> session(CreateSession(&session_deps_));
  HttpNetworkTransaction trans(DEFAULT_PRIORITY, session.get());

  TestCompletionCallback callback;
  int rv = trans.Start(&request_info, callback.callback(), NetLogWithSource());
  if (rv == ERR_IO_PENDING)
    rv = callback.WaitForResult();
  ASSERT_EQ(error, rv);
}
