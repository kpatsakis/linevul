url::Parsed::ComponentType TemplateURLRef::GetSearchTermKeyLocation(
    const SearchTermsData& search_terms_data) const {
  ParseIfNecessary(search_terms_data);
  return search_term_key_location_;
}
