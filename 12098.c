void RangeTransactionServer::RangeHandler(const net::HttpRequestInfo* request,
                                          std::string* response_status,
                                          std::string* response_headers,
                                          std::string* response_data) {
  if (request->extra_headers.IsEmpty()) {
    response_status->assign("HTTP/1.1 416 Requested Range Not Satisfiable");
    response_data->clear();
    return;
  }

  EXPECT_TRUE(request->extra_headers.HasHeader(kExtraHeaderKey));

  if (not_modified_) {
    response_status->assign("HTTP/1.1 304 Not Modified");
    response_data->clear();
    return;
  }

  std::vector<net::HttpByteRange> ranges;
  std::string range_header;
  if (!request->extra_headers.GetHeader(
          net::HttpRequestHeaders::kRange, &range_header) ||
      !net::HttpUtil::ParseRangeHeader(range_header, &ranges) || bad_200_ ||
      ranges.size() != 1) {
    response_status->assign("HTTP/1.1 200 OK");
    response_headers->assign("Date: Wed, 28 Nov 2007 09:40:09 GMT");
    response_data->assign("Not a range");
    return;
  }

  net::HttpByteRange byte_range = ranges[0];
  if (byte_range.first_byte_position() > 79) {
    response_status->assign("HTTP/1.1 416 Requested Range Not Satisfiable");
    response_data->clear();
    return;
  }

  EXPECT_TRUE(byte_range.ComputeBounds(80));
  int start = static_cast<int>(byte_range.first_byte_position());
  int end = static_cast<int>(byte_range.last_byte_position());

  EXPECT_LT(end, 80);

  std::string content_range = base::StringPrintf(
      "Content-Range: bytes %d-%d/80\n", start, end);
  response_headers->append(content_range);

  if (!request->extra_headers.HasHeader("If-None-Match") || modified_) {
    std::string data;
    if (end == start) {
      EXPECT_EQ(0, end % 10);
      data = "r";
    } else {
      EXPECT_EQ(9, (end - start) % 10);
      for (int block_start = start; block_start < end; block_start += 10) {
        base::StringAppendF(&data, "rg: %02d-%02d ",
                            block_start, block_start + 9);
      }
    }
    *response_data = data;

    if (end - start != 9) {
      int len = end - start + 1;
      std::string content_length = base::StringPrintf("Content-Length: %d\n",
                                                      len);
      response_headers->replace(response_headers->find("Content-Length:"),
                                content_length.size(), content_length);
    }
  } else {
    response_status->assign("HTTP/1.1 304 Not Modified");
    response_data->clear();
  }
}
