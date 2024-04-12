RequestQuery ParseQuery(const GURL& url) {
  RequestQuery queries;
  for (QueryIterator it(url); !it.IsAtEnd(); it.Advance()) {
    std::string unescaped_query;
    UnescapeBinaryURLComponent(
        it.GetKey(), UnescapeRule::REPLACE_PLUS_WITH_SPACE, &unescaped_query);
    queries[unescaped_query].push_back(it.GetUnescapedValue());
  }
  return queries;
}
