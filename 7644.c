void AutocompletePopupViewGtk::AcceptLine(size_t line,
                                          WindowOpenDisposition disposition) {
  const AutocompleteMatch& match = model_->result().match_at(line);
  const GURL url(match.destination_url);
  std::wstring keyword;
  const bool is_keyword_hint = model_->GetKeywordForMatch(match, &keyword);
  edit_view_->OpenURL(url, disposition, match.transition, GURL(), line,
                      is_keyword_hint ? std::wstring() : keyword);
}
