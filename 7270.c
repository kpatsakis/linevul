void CheckAdjustedOffsets(const std::string& url_string,
                          FormatUrlTypes format_types,
                          net::UnescapeRule::Type unescape_rules,
                          const size_t* output_offsets) {
  GURL url(url_string);
  size_t url_length = url_string.length();
  std::vector<size_t> offsets;
  for (size_t i = 0; i <= url_length + 1; ++i)
    offsets.push_back(i);
  offsets.push_back(500000);  // Something larger than any input length.
  offsets.push_back(std::string::npos);
  base::string16 formatted_url = FormatUrlWithOffsets(url, format_types,
      unescape_rules, nullptr, nullptr, &offsets);
  for (size_t i = 0; i < url_length; ++i)
    VerboseExpect(output_offsets[i], offsets[i], url_string, i, formatted_url);
  VerboseExpect(formatted_url.length(), offsets[url_length], url_string,
                url_length, formatted_url);
  VerboseExpect(base::string16::npos, offsets[url_length + 1], url_string,
                500000, formatted_url);
  VerboseExpect(base::string16::npos, offsets[url_length + 2], url_string,
                std::string::npos, formatted_url);
}
