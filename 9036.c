bool Extension::LoadExtent(const char* key,
                           URLPatternSet* extent,
                           const char* list_error,
                           const char* value_error,
                           string16* error) {
  Value* temp_pattern_value = NULL;
  if (!manifest_->Get(key, &temp_pattern_value))
    return true;

  if (temp_pattern_value->GetType() != Value::TYPE_LIST) {
    *error = ASCIIToUTF16(list_error);
    return false;
  }

  ListValue* pattern_list = static_cast<ListValue*>(temp_pattern_value);
  for (size_t i = 0; i < pattern_list->GetSize(); ++i) {
    std::string pattern_string;
    if (!pattern_list->GetString(i, &pattern_string)) {
      *error = ErrorUtils::FormatErrorMessageUTF16(value_error,
                                                       base::UintToString(i),
                                                       errors::kExpectString);
      return false;
    }

    URLPattern pattern(kValidWebExtentSchemes);
    URLPattern::ParseResult parse_result = pattern.Parse(pattern_string);
    if (parse_result == URLPattern::PARSE_ERROR_EMPTY_PATH) {
      pattern_string += "/";
      parse_result = pattern.Parse(pattern_string);
    }

    if (parse_result != URLPattern::PARSE_SUCCESS) {
      *error = ErrorUtils::FormatErrorMessageUTF16(
          value_error,
          base::UintToString(i),
          URLPattern::GetParseResultString(parse_result));
      return false;
    }

    if (pattern.match_all_urls()) {
      *error = ErrorUtils::FormatErrorMessageUTF16(
          value_error,
          base::UintToString(i),
          errors::kCannotClaimAllURLsInExtent);
      return false;
    }

    if (pattern.host().empty()) {
      *error = ErrorUtils::FormatErrorMessageUTF16(
          value_error,
          base::UintToString(i),
          errors::kCannotClaimAllHostsInExtent);
      return false;
    }

    if (pattern.path().find('*') != std::string::npos) {
      *error = ErrorUtils::FormatErrorMessageUTF16(
          value_error,
          base::UintToString(i),
          errors::kNoWildCardsInPaths);
      return false;
    }
    pattern.SetPath(pattern.path() + '*');

    extent->AddPattern(pattern);
  }

  return true;
}
