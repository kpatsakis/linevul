bool TemplateURL::ReplaceSearchTermsInURL(
    const GURL& url,
    const TemplateURLRef::SearchTermsArgs& search_terms_args,
    const SearchTermsData& search_terms_data,
    GURL* result) {
  url::Parsed::ComponentType search_term_component;
  url::Component search_terms_position;
  base::string16 search_terms;
  if (!FindSearchTermsInURL(url, search_terms_data, &search_terms,
                            &search_term_component, &search_terms_position)) {
    return false;
  }
  DCHECK(search_terms_position.is_nonempty());

  const bool is_in_query = (search_term_component != url::Parsed::PATH);

  std::string input_encoding;
  base::string16 encoded_terms;
  base::string16 encoded_original_query;
  EncodeSearchTerms(search_terms_args, is_in_query, &input_encoding,
                    &encoded_terms, &encoded_original_query);

  std::string old_params;
  if (search_term_component == url::Parsed::QUERY) {
    old_params = url.query();
  } else if (search_term_component == url::Parsed::REF) {
    old_params = url.ref();
  } else {
    DCHECK_EQ(search_term_component, url::Parsed::PATH);
    old_params = url.path();
  }

  std::string new_params(old_params, 0, search_terms_position.begin);
  new_params += base::UTF16ToUTF8(encoded_terms);
  new_params += old_params.substr(search_terms_position.end());
  GURL::Replacements replacements;

  if (search_term_component == url::Parsed::QUERY) {
    replacements.SetQueryStr(new_params);
  } else if (search_term_component == url::Parsed::REF) {
    replacements.SetRefStr(new_params);
  } else {
    DCHECK_EQ(search_term_component, url::Parsed::PATH);
    replacements.SetPathStr(new_params);
  }

  *result = url.ReplaceComponents(replacements);
  return true;
}
