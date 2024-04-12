void CreateTruncatedEntry(std::string raw_headers, MockHttpCache* cache) {
  disk_cache::Entry* entry;
  ASSERT_TRUE(cache->CreateBackendEntry(kRangeGET_TransactionOK.url, &entry,
                                        NULL));

  raw_headers = net::HttpUtil::AssembleRawHeaders(raw_headers.data(),
                                                  raw_headers.size());

  net::HttpResponseInfo response;
  response.response_time = base::Time::Now();
  response.request_time = base::Time::Now();
  response.headers = new net::HttpResponseHeaders(raw_headers);
  EXPECT_TRUE(MockHttpCache::WriteResponseInfo(entry, &response, true, true));

  scoped_refptr<net::IOBuffer> buf(new net::IOBuffer(100));
  int len = static_cast<int>(base::strlcpy(buf->data(),
                                           "rg: 00-09 rg: 10-19 ", 100));
  net::TestCompletionCallback cb;
  int rv = entry->WriteData(1, 0, buf, len, cb.callback(), true);
  EXPECT_EQ(len, cb.GetResult(rv));
  entry->Close();
}
