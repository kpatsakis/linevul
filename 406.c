std::string TemplateURLRef::ReplaceSearchTerms(
    const SearchTermsArgs& search_terms_args,
    const SearchTermsData& search_terms_data,
    PostContent* post_content) const {
  ParseIfNecessary(search_terms_data);
  if (!valid_)
    return std::string();

  std::string url(HandleReplacements(search_terms_args, search_terms_data,
                                     post_content));

  GURL gurl(url);
  if (!gurl.is_valid())
    return url;

  std::vector<std::string> query_params;
  if (search_terms_args.append_extra_query_params) {
    std::string extra_params(
        base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
            switches::kExtraSearchQueryParams));
    if (!extra_params.empty())
      query_params.push_back(extra_params);
  }
  if (!search_terms_args.suggest_query_params.empty())
    query_params.push_back(search_terms_args.suggest_query_params);
  if (!gurl.query().empty())
    query_params.push_back(gurl.query());

  if (query_params.empty())
    return url;

  GURL::Replacements replacements;
  std::string query_str = base::JoinString(query_params, "&");
  replacements.SetQueryStr(query_str);
  return gurl.ReplaceComponents(replacements).possibly_invalid_spec();
}
