bool SplitStringIntoKeyValuePairs(
    const std::string& line,
    char key_value_delimiter,
    char key_value_pair_delimiter,
    std::vector<std::pair<std::string, std::string> >* kv_pairs) {
  kv_pairs->clear();

  std::vector<std::string> pairs;
  SplitString(line, key_value_pair_delimiter, &pairs);

  bool success = true;
  for (size_t i = 0; i < pairs.size(); ++i) {
    if (pairs[i].empty())
      continue;

    std::string key;
    std::vector<std::string> value;
    if (!SplitStringIntoKeyValues(pairs[i],
                                  key_value_delimiter,
                                  &key, &value)) {
      success = false;
    }
    DCHECK_LE(value.size(), 1U);
    kv_pairs->push_back(make_pair(key, value.empty()? "" : value[0]));
  }
  return success;
}
