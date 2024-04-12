void HttpResponseHeaders::AddHopContentRangeHeaders(HeaderSet* result) {
  result->insert("content-range");
}
