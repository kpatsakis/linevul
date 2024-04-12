void AutocompleteInput::Clear() {
  text_.clear();
  type_ = INVALID;
  parts_ = url_parse::Parsed();
  scheme_.clear();
  desired_tld_.clear();
  prevent_inline_autocomplete_ = false;
  prefer_keyword_ = false;
}
